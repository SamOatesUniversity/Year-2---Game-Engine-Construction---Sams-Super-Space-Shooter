#include "SpaceShip.h"

void createSpaceShip( CSpaceShip *spaceShip, CExplosion *explosion, CWorld *world )
{
	if( !world->addEntity( spaceShip, "images/space_ship.png" ) ) HAPI->Close();
	spaceShip->init();

	if( !world->addEntity( spaceShip->getBullet( 0 ), "images/bullet.png" ) ) HAPI->Close();
	spaceShip->getBullet( 0 )->init();
	for( int i = 1; i < spaceShip->getBulletCount(); i++ )
	{
		if( !world->cloneEntity( spaceShip->getBullet( 0 ), spaceShip->getBullet( i ) ) ) HAPI->Close();
		spaceShip->getBullet( i )->init();
	}

	CExplosion *expl = spaceShip->getExplosion();
	if( !world->cloneEntity( explosion, expl ) ) HAPI->Close();	
	expl->init();
}

CSpaceShip::CSpaceShip(void)
{
	m_explosion = new CExplosion();
	m_iBulletCount = 14;
	for( int i = 0; i < m_iBulletCount; i++ ) m_bullet.push_back( new CBullet() );
	CWebBrowser::Instance().Create();
}

CSpaceShip::~CSpaceShip(void)
{
}

void CSpaceShip::init( void )
{
	m_iFrameCount = 4;
	m_iActiveFrame = 0;
	m_Speed = 0;
	m_Turn = 0;
	m_iX = 100;
	m_iY = (int)( (m_iScreenHeight * 0.5f) - ( m_iHeight * 0.5f ) );
	m_iWidth /= m_iFrameCount;
	m_fireTimer = (float)HAPI->GetTime();
	m_rightWingBullet = false;
	m_iActiveBullet = 0;
	m_side = TSidePlayer;
	m_iScore = 0;
	m_iDifficulty = 1;
}

void CSpaceShip::update( void )
{
	if( m_isActive )
	{
		HAPI_TKeyboardData kb;
		HAPI->GetKeyboardData( &kb );

		if( kb.scanCode[HK_RIGHT] )
			m_Speed += 4.0f;

		if( kb.scanCode[HK_LEFT] )
			m_Speed -= 4.0f;

		if( m_Speed > 70.0f ) m_Speed = 70.0f;
		if( m_Speed < -70.0f ) m_Speed = -70.0f;

		if( m_Speed < 0.0f ) m_Speed += 1.0f;
		if( m_Speed > 0.0f ) m_Speed -= 1.0f;

		m_iX += (int)( m_Speed * 0.1f );
		if( m_iX < 0 )
		{
			m_iX = 0;
			m_Speed = 0.0f;
		}

		if( m_iX > m_iScreenWidth - m_iWidth )
		{
			m_iX = m_iScreenWidth - m_iWidth;
			m_Speed = 0.0f;
		}

		if( kb.scanCode[HK_UP] )
			m_Turn -= 4.0f;

		if( kb.scanCode[HK_DOWN] )
			m_Turn += 4.0f;

		if( m_Turn > 200.0f ) m_Turn = 200.0f;
		if( m_Turn < -200.0f ) m_Turn = -200.0f;

		if( m_Turn < 0.0f ) m_Turn += 1.0f;
		if( m_Turn > 0.0f ) m_Turn -= 1.0f;

		m_iY += (int)( m_Turn * 0.1f );
		if( m_iY < 0 )
		{
			m_iY = 0;
			m_Turn = 0.0f;
		}

		if( m_iY > m_iScreenHeight - (2 * m_iHeight ) )
		{
			m_iY = m_iScreenHeight - (2 * m_iHeight );
			m_Turn = 0.0f;
		}

		m_iActiveFrame++;
		if( m_iActiveFrame >= m_iFrameCount ) m_iActiveFrame = 0;

		if( kb.scanCode[HK_SPACE] && (float)HAPI->GetTime() - m_fireTimer >= 100 )
		{
			m_fireTimer = (float)HAPI->GetTime();
			if( m_rightWingBullet )
				m_bullet[m_iActiveBullet]->fire( m_iX, m_iY + m_iHeight - m_bullet[m_iActiveBullet]->getHeight() );
			else
				m_bullet[m_iActiveBullet]->fire( m_iX, m_iY );
			m_rightWingBullet = !m_rightWingBullet;
			m_iActiveBullet++;
			if( m_iActiveBullet >= m_iBulletCount ) m_iActiveBullet = 0;
		}

		for( int i = 0; i < m_iBulletCount; i++ )
		{
			m_iScore += (int)m_bullet[i]->hitEnemy() * ( 25 * m_iDifficulty );
		}
  	}
}

void CSpaceShip::kill( void )
{
	if( m_isActive )
	{
		m_iHealth -= 1 * m_iDifficulty;
		if( m_iHealth <= 0 )
		{
			m_explosion->position( m_iX, m_iY );
			m_explosion->setActive( true );
			m_isActive = false;
			m_iX = m_iScreenWidth + m_iWidth;
			char sz_url[255], sz_score[64];
			_itoa_s( m_iScore, sz_score, 10 );
			strcpy_s( sz_url, "http://samoatesgames.com/uni/GEC/space-fb.php?score=" );
			strcat_s( sz_url, sz_score );
			CWebBrowser::Instance().NavigateTo( sz_url );
		}
	}
}

void CSpaceShip::restart( void )
{
	m_iActiveFrame = 0;
	m_Speed = 0;
	m_Turn = 0;
	m_iX = 100;
	m_iY = (int)( (m_iScreenHeight * 0.5f) - ( m_iHeight * 0.5f ) );
	m_fireTimer = (float)HAPI->GetTime();
	m_rightWingBullet = false;
	m_iActiveBullet = 0;
	m_iScore = 0;
	m_iHealth = 100;
	m_isActive = true;
}
