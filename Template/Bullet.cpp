#include "Bullet.h"


CBullet::CBullet(void)
{
}

CBullet::~CBullet(void)
{
}

void CBullet::init( void )
{
	m_isActive = false;
	m_hitEnemy = false;
	m_iFrameCount = 4;
	m_iActiveFrame = 0;
	m_iX = -100;
	m_iY = -100;
	m_iWidth /= m_iFrameCount;
	m_side = TSidePlayer;
}

void CBullet::update( void )
{
	if( m_isActive ) 
		m_iX += 12;

	if( m_iX > m_iScreenWidth )
	{
		m_iX = -100;
		m_isActive = false;
	}

	m_iActiveFrame++;
	if( m_iActiveFrame >= m_iFrameCount ) m_iActiveFrame = 0;
}

void CBullet::kill( void )
{
	m_isActive = false;
	m_iX = -100;
	m_hitEnemy = true;
}

void CBullet::fire( const int x, const int y )
{
	m_iX = x;
	m_iY = y;
	m_isActive = true;
}
