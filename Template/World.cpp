#include "world.h"


CWorld::CWorld(void)
{
	m_tickRate = 60.0f;
	m_ftpDetails.servername = NULL;
}

CWorld::~CWorld(void)
{
	delete m_vis;
	for( unsigned int i = 0; i < m_vEntity.size(); i++ )
		delete m_vEntity[i];
}

bool CWorld::init( int width, int height )
{
	m_iScreenWidth = width;
	m_iScreenHeight = height;

	m_vis = new CVisualisation();
	if( !m_vis->init( width, height ) )
	{
		HAPI->UserMessage( "An internal error has occured", "Core Error!" );
		return false;
	}

	HAPI->SetShowFPS( true );
	m_coreTimer = (float)HAPI->GetTime();
	SetWindowText( GetActiveWindow(), "Sam's Super Space Shooter" );

	return true;
}

void CWorld::setFtpDetails( char* server_address, char* username, char* password, char *directory )
{
	m_ftpDetails.servername = server_address;
	m_ftpDetails.username = username;
	m_ftpDetails.password = password;
	m_ftpDetails.directory = directory;
	m_ftpDetails.port = INTERNET_DEFAULT_FTP_PORT;
}

bool CWorld::addEntity( CWorldEntity *entity, char *imageLocation, TDraw drawType )
{
	bool res = true;

	if( !FileExists( imageLocation ) ) 
	{
		std::string str, remotedir;
		str = imageLocation;
		int found = str.find( "/" );
		if( found != std::string::npos )
		{
			remotedir = str.substr( 0, found + 1 );
			str = str.replace( 0, found + 1, "" );
		}
		FTP_Download( m_ftpDetails, (char*)str.c_str(), imageLocation, (char*)remotedir.c_str() );
	}

	int id = 0;
	if( !m_vis->createSprite( id, imageLocation, drawType ) )
		res = false;

	entity->setId( id );
	entity->setSpriteDimensions( m_vis->getWidth( id ), m_vis->getHeight( id ) );
	entity->setScreenDimensions( m_iScreenWidth, m_iScreenHeight );
	m_vEntity.push_back( entity );

	return res;
}

bool CWorld::cloneEntity( CWorldEntity *source_entity, CWorldEntity *entity )
{
	bool res = true;
	int id = 0;
	if( !m_vis->cloneSprite( id, source_entity->getId() ) )
		res = false;

	entity->setId( id );
	entity->setSpriteDimensions( m_vis->getWidth( id ), m_vis->getHeight( id ) );
	entity->setScreenDimensions( m_iScreenWidth, m_iScreenHeight );
	m_vEntity.push_back( entity );

	return res;
}

bool CWorld::addSound( int &id, char *soundLocation )
{
	bool res = true;

	if( !FileExists( soundLocation ) ) 
	{
		std::string str, remotedir;
		str = soundLocation;
		int found = str.find( "/" );
		if( found != std::string::npos )
		{
			remotedir = str.substr( 0, found + 1 );
			str = str.replace( 0, found + 1, "" );
		}
		FTP_Download( m_ftpDetails, (char*)str.c_str(), soundLocation, (char*)remotedir.c_str() );
	}

	CSound::Instance().loadSound( id, soundLocation );

	return res;
}

void CWorld::update( void )
{
	if( (float)HAPI->GetTime() - m_coreTimer > ( 1000.0f / m_tickRate ) )
	{
		m_coreTimer = (float)HAPI->GetTime();
		for( unsigned int i = 0; i < m_vEntity.size(); i++ )
		{
			m_vis->setActive( m_vEntity[i]->getId(), m_vEntity[i]->isActive() );
				
			m_vEntity[i]->update();

			m_vis->update( m_vEntity[i]->getId(), m_vEntity[i]->getX(), m_vEntity[i]->getY(), 
							m_vEntity[i]->getActiveFrame(), m_vEntity[i]->getFrameCount() );
		

			if( m_vEntity[i]->getSide() != TSideNeutral )
			{
				TSide ent_side = m_vEntity[i]->getSide();
				TSide enemy_side = ( ent_side == TSidePlayer ) ? TSideEnemy : TSidePlayer;
				for( unsigned int j = 0; j < m_vEntity.size(); j++ )
				{
					if( m_vEntity[j]->getSide() == enemy_side )
					{
						//check for collisions
						if( m_vEntity[i]->getX() > m_vEntity[j]->getX() && 
							m_vEntity[i]->getX() < m_vEntity[j]->getX() + m_vEntity[j]->getWidth() )
						{
							//x collision
							if( m_vEntity[i]->getY() > m_vEntity[j]->getY() && 
								m_vEntity[i]->getY() < m_vEntity[j]->getY() + m_vEntity[j]->getHeight() )
							{
								//y collision
								m_vEntity[i]->kill();
								m_vEntity[j]->kill();
							}
						}
					}
				}
			}
		}
	}

	float s = ( (float)HAPI->GetTime() - m_coreTimer ) / ( ( m_coreTimer + ( 1000.0f / m_tickRate ) ) - m_coreTimer );
	for( unsigned int i = 0; i < m_vEntity.size(); i++ )
		if( m_vEntity[i]->isActive() && m_vEntity[i]->useLerp() ) m_vis->lerp( m_vEntity[i]->getId(), m_vEntity[i]->getX(), m_vEntity[i]->getY(), s );

	m_vis->draw( );
}