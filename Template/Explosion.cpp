#include "Explosion.h"

CExplosion::CExplosion(void)
{
}

CExplosion::~CExplosion(void)
{
}

void CExplosion::init( void )
{
	m_iFrameCount = 8;
	m_iActiveFrame = 0;
	m_iWidth /= m_iFrameCount;
	m_iX = -m_iWidth;
	m_iY = -m_iHeight;
	m_side = TSideNeutral;
	m_isActive = false;
	m_useLerp = false;
}

void CExplosion::update( void )
{
	if( m_isActive )
	{
		m_iActiveFrame++;
		if( m_iActiveFrame >= m_iFrameCount )
		{
			CSound::Instance().playSound( soundExplosion );
			m_iX = -100;
			m_isActive = false;
			m_iActiveFrame = 0;
		}
	}
}
	
void CExplosion::kill( void )
{

}