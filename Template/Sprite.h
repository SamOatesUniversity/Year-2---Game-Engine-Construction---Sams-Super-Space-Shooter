#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"

enum TDraw
{
	Tnormal = 1,
	Tfast = 2,
	Tbackground = 3
};

class CSprite
{
private:
	BYTE *m_imageData, *m_screenData;
	int m_iWidth, m_iHeight;
	int m_iX, m_iY, m_iLx, m_iLy;
	int m_iActiveFrame, m_iFrameCount;
	bool m_isClone, m_isActive;

	CRectangle *m_rect;
	TDraw m_drawType;
public:
	CSprite(void);
	~CSprite(void);

	void copy( CSprite *source );

	bool init( char* imageLocation, TDraw drawType );
	void draw( CRectangle *destination );

	BYTE *getImageData( void ) { return m_imageData; }
	TDraw getDrawType( void ) { return m_drawType; }

	void setX( const int x ) { setXY( x, m_iY ); }
	void setY( const int y ) { setXY( m_iX, y ); }
	void setXY( const int x, const int y );
	void setLastXY( const int x, const int y );

	void setAnimation( const int activeFrame, const int frameCount );

	const int getLastX( void ) { return m_iLx; }
	const int getLastY( void ) { return m_iLy; }

	const int getWidth( void ) { return m_iWidth; }
	const int getHeight( void ) { return m_iHeight; }

	void setActive(  const bool active ) { m_isActive; }
	const bool isActive( void ) { return m_isActive; }
};

