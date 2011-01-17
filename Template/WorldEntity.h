#pragma once

#include "Sound.h"
#include "Visualisation.h"

enum TSide
{
	TSideNeutral,
	TSidePlayer,
	TSideEnemy
};

class CWorldEntity
{
protected:
	int m_id, m_iX, m_iY, m_iHealth;
	int m_iFrameCount, m_iActiveFrame;
	int m_iWidth, m_iHeight, m_iScreenWidth, m_iScreenHeight;
	TSide m_side;
	bool m_isActive, m_useLerp;
public:
	CWorldEntity(void);
	virtual ~CWorldEntity(void) = 0;

	virtual void update( void ) = 0;
	virtual void kill( void ) = 0;

	void setScreenDimensions( const int width, const int height );
	void setSpriteDimensions( const int width, const int height );

	void setId( const int id );
	const int getId( void );

	TSide getSide( void ) { return m_side; }

	const int getHealth( void ) { return m_iHealth; }
	const int getX( void ) { return m_iX; }
	const int getY( void ) { return m_iY; }
	const int getWidth( void ) { return m_iWidth; }
	const int getHeight( void ) { return m_iHeight; }
	const int getActiveFrame( void ) { return m_iActiveFrame; }
	const int getFrameCount( void ) { return m_iFrameCount; }

	const bool isActive( void ) { return m_isActive; }
	void setActive( const bool active ) { m_isActive = active; }

	const bool useLerp( void ) { return m_useLerp; }

	void position( const int x, const int y ) { m_iX = x; m_iY = y; }
};

