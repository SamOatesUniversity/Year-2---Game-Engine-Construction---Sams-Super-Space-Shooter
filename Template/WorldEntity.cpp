#include "WorldEntity.h"


CWorldEntity::CWorldEntity(void)
{
	m_iX = 0;
	m_iY = 0;
	m_id = -1;

	m_iFrameCount = 1;
	m_iActiveFrame = 0;
	m_isActive = true;
	m_useLerp = true;

	m_iHealth = 100;
}

CWorldEntity::~CWorldEntity(void)
{
}

void CWorldEntity::setId( const int id )
{
	m_id = id;
}

const int CWorldEntity::getId( void )
{
	return m_id;
}

void CWorldEntity::setSpriteDimensions( const int width, const int height )
{
	m_iWidth = width;
	m_iHeight = height;
}

void CWorldEntity::setScreenDimensions( const int width, const int height )
{
	m_iScreenWidth = width;
	m_iScreenHeight = height;
}