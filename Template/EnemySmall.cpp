#include "EnemySmall.h"

void createSmallEnemy( CEnemySmall *enemy, CExplosion *explosion, CWorld *world )
{
	if( !world->addEntity( enemy, "images/enemy_small.png" ) ) HAPI->Close();
	enemy->init( 0 );

	if( !world->addEntity( enemy->getBullet( 0 ), "images/enemy_small_bullets.png" ) ) HAPI->Close();
	enemy->getBullet( 0 )->init();
	for( int i = 1; i < enemy->getBulletCount(); i++ )
	{
		if( !world->cloneEntity( enemy->getBullet( 0 ), enemy->getBullet( i ) ) ) HAPI->Close();
		enemy->getBullet( i )->init();
	}

	if( !world->cloneEntity( explosion, enemy->getExplosion() ) ) HAPI->Close();
	enemy->getExplosion()->init();
	enemy->setActive( false );
}

void createSmallEnemy( CEnemySmall *enemy, CEnemySmall *source, CExplosion *explosion, CWorld *world )
{
	if( !world->cloneEntity( source, enemy ) ) HAPI->Close();
	enemy->init( 0 );

	if( !world->addEntity( enemy->getBullet( 0 ), "images/enemy_small_bullets.png" ) ) HAPI->Close();
	enemy->getBullet( 0 )->init();
	for( int i = 1; i < enemy->getBulletCount(); i++ )
	{
		if( !world->cloneEntity( enemy->getBullet( 0 ), enemy->getBullet( i ) ) ) HAPI->Close();
		enemy->getBullet( i )->init();
	}

	if( !world->cloneEntity( explosion, enemy->getExplosion() ) ) HAPI->Close();
	enemy->getExplosion()->init();
	enemy->setActive( false );
}

CEnemySmall::CEnemySmall(void)
{
	m_explosion = new CExplosion();
	m_iBulletCount = 4;
	for( int i = 0; i < m_iBulletCount; i++ ) m_bullet.push_back( new CEnemyBullet() );
}

CEnemySmall::~CEnemySmall(void)
{
}

void CEnemySmall::init( const int offset )
{
	m_iFrameCount = 4;
	m_iActiveFrame = 0;
	m_iWidth /= m_iFrameCount;
	m_iX = m_iScreenWidth + ( ( m_iWidth * 2 ) * offset );
	m_iY = 300;
	m_Offset = offset * 0.5f;
	m_attack = true;
	m_side = TSideEnemy;
	m_iActiveBullet = 1;
	m_fireTimer = (float)HAPI->GetTime();
	m_iHealth = 1;
}

void CEnemySmall::reset( void )
{
	for( int i = 0; i < m_iBulletCount; i++ )
	{
		m_bullet[i]->position( m_iScreenWidth, 0 );
		m_bullet[i]->setActive( false );
	}
}

void CEnemySmall::update( void )
{
	if( m_isActive )
	{
		if( m_attack )
			m_iX--;
		else
			m_iX++;

		m_iY = (int)( ( (m_iScreenHeight * 0.5f) - (m_iHeight * 0.5f) - 32.0f ) + sin( m_Offset += 0.02f ) * 248.0f );

		if( m_iX < (int)(m_iScreenWidth * 0.5f) ) m_attack = false;
		if( m_iX > m_iScreenWidth - m_iWidth ) m_attack = true;

		if( (float)HAPI->GetTime() - m_fireTimer > 2000 && m_iX < ( m_iScreenWidth - m_iWidth ) )
		{
			m_fireTimer = (float)HAPI->GetTime();
			m_bullet[m_iActiveBullet]->fire( m_iX, m_iY + (int)(m_iHeight * 0.5f) );
			m_iActiveBullet++;
			if( m_iActiveBullet >= m_iBulletCount ) m_iActiveBullet = 0;
		}

		m_iActiveFrame++;
		if( m_iActiveFrame >= m_iFrameCount ) m_iActiveFrame = 0;
	}
}

void CEnemySmall::kill( void )
{
	m_iHealth--;
	if( m_iHealth <= 0 )
	{
		m_iHealth = 1;
		m_explosion->position( m_iX, m_iY );
		m_explosion->setActive( true );
		m_isActive = false;
		m_iX = m_iScreenWidth + m_iWidth;
	}
}


