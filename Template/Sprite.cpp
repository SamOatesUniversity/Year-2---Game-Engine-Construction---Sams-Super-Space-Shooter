#include "Sprite.h"


CSprite::CSprite(void)
{
	m_iWidth = NULL;
	m_iHeight = NULL;
	m_iX = 0;
	m_iY = 0;
	m_iLx = 0;
	m_iLy = 0;

	m_imageData = NULL;
	m_screenData = HAPI->GetScreenPointer();

	m_drawType = Tnormal;

	m_isClone = false;
	m_isActive = true;
}

CSprite::~CSprite(void)
{
	delete m_rect;
	if( m_imageData && !m_isClone ) delete[] m_imageData;
}

void CSprite::copy( CSprite *source )
{
	m_imageData = source->getImageData();
	m_screenData = HAPI->GetScreenPointer();
	m_iWidth = source->getWidth();
	m_iHeight = source->getHeight();
	m_drawType = source->getDrawType();
	m_rect = new CRectangle( 0, 0, m_iWidth, m_iHeight );
	m_isClone = true;
}

bool CSprite::init( char* imageLocation, TDraw drawType )
{
	bool res = true;

	if( !HAPI->LoadTexture( imageLocation, &m_imageData, &m_iWidth, &m_iHeight ) )
		res = false;

	m_rect = new CRectangle( 0, 0, m_iWidth, m_iHeight );

	m_drawType = drawType;
	
	return res;
}

void CSprite::draw( CRectangle *destination )
{
	BYTE *screen = NULL, *imgPtr = NULL;
	int frameWidth = m_iWidth / m_iFrameCount;

	switch( m_drawType )
	{
	case Tnormal:
		//the default, supports full alpha.
		//per pixel
		m_rect->clipTo( destination );
		imgPtr = m_imageData + (( m_rect->getClipX1() + (m_rect->getClipY1() * m_iWidth )) * 4);
		imgPtr += ( m_iActiveFrame * frameWidth ) * 4;
		for( int ty = m_iY + m_rect->getClipY1(); ty < m_iY + m_rect->getClipY2(); ty++ )
		{
			for( int tx = m_iX + m_rect->getClipX1(); tx < m_iX + m_rect->getClipX2(); tx++ )
			{
				//check if the pixel has any alpha
				if( imgPtr[3] > 0 )
				{
					//if full alpha, copy image over background
					if( imgPtr[3] == 255 )
					{
						screen = m_screenData + ( ( ( tx ) + ( ( ty ) * destination->getAbsoluteW() ) ) * 4);
						memcpy( screen, imgPtr, 4 );	
					}
					//otherwise merge the image and background colours respectivly
					else
					{
						screen = m_screenData + ( ( ( tx ) + ( ( ty ) * destination->getAbsoluteW() ) ) * 4);
						screen[0]=screen[0]+((imgPtr[3]*(imgPtr[0]-screen[0])) >> 8);
						screen[1]=screen[1]+((imgPtr[3]*(imgPtr[1]-screen[1])) >> 8);
						screen[2]=screen[2]+((imgPtr[3]*(imgPtr[2]-screen[2])) >> 8);
					}
				}
				imgPtr += 4;
			}
			imgPtr += ( m_iWidth - ( m_rect->getClipX2() - m_rect->getClipX1() ) ) * 4;
		}
		break;

	case Tfast:
		//Fast Draw, ignores alpha
		m_rect->clipTo( destination );
		imgPtr = m_imageData + (( m_rect->getClipX1() + (m_rect->getClipY1() * m_rect->getAbsoluteW() )) * 4);
		for( int ty = m_iY + m_rect->getClipY1(); ty < m_iY + m_rect->getClipY2(); ty++ )
		{
			screen = m_screenData + ( ( ( m_iX + m_rect->getClipX1() ) + ( ty * destination->getAbsoluteW() ) ) * 4);
			memcpy( screen, imgPtr, ( m_rect->getClipX2() - m_rect->getClipX1() ) * 4 );	
			imgPtr += m_rect->getAbsoluteW() * 4;
		}
		break;

	case Tbackground:
		//does a full background draw. fast
		if( m_iX < 0 ) m_iX = 0;

		imgPtr = m_imageData + ( m_iX * 4 );
		for( int i = 0; i < destination->getAbsoluteH(); i++ )
		{
			screen = m_screenData + ( ( i * destination->getAbsoluteW() ) * 4);
			memcpy( screen, imgPtr, destination->getAbsoluteW() * 4 );
			imgPtr += m_iWidth * 4;
		}
		break;
	}
}

void CSprite::setAnimation( const int activeFrame, const int frameCount )
{
	m_iActiveFrame = activeFrame;
	m_iFrameCount = frameCount;
	int frameWidth = m_iWidth / frameCount;
	m_rect->update( 0, 0, frameWidth, m_iHeight );
}

void CSprite::setXY( const int x, const int y )
{
	m_iX = x;
	m_iY = y;
	m_rect->position( x, y );
}

void CSprite::setLastXY( const int x, const int y )
{
	m_iLx = x;
	m_iLy = y;
}
