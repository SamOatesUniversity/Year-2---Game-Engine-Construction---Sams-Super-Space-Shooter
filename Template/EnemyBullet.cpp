#include "EnemyBullet.h"

CEnemyBullet::CEnemyBullet(void)
{
}

CEnemyBullet::~CEnemyBullet(void)
{
}

void CEnemyBullet::init( void )
{
	m_isActive = false;
	m_iFrameCount = 8;
	m_iActiveFrame = 0;
	m_iX = -100;
	m_iY = -100;
	m_iWidth /= m_iFrameCount;
	m_side = TSideEnemy;
}

void CEnemyBullet::update( void )
{
	if( m_isActive ) 
		m_iX -= 12;

	if( m_iX < -m_iWidth )
	{
		m_iX = -100;
		m_isActive = false;
	}

	m_iActiveFrame++;
	if( m_iActiveFrame >= m_iFrameCount ) m_iActiveFrame = 0;
}

void CEnemyBullet::kill( void )
{
	m_isActive = false;
	m_iX = -100;
}

void CEnemyBullet::fire( const int x, const int y )
{
	m_iX = x;
	m_iY = y;
	m_isActive = true;
}
