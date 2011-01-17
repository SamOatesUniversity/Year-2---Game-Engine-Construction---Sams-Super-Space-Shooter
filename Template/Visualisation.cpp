#include "Visualisation.h"


CVisualisation::CVisualisation(void)
{
	m_bBackdrop = true;
}

CVisualisation::~CVisualisation(void)
{
	delete m_rect;
	delete[] m_backdropColour;
	for( unsigned int i = 0; i < m_vSprite.size(); i++ )
		delete m_vSprite[i];
}

bool CVisualisation::init( int width, int height )
{
	m_iWidth = width;
	m_iHeight = height;

	if( !HAPI->Initialise( &m_iWidth, &m_iHeight ) )
		return false;

	m_rect = new CRectangle( 0, 0, m_iWidth, m_iHeight );
	m_backdropColour = new BYTE[m_iWidth * m_iHeight * 4];

	setBackdropColour( 0, 0, 0 );

	return true;
}

void CVisualisation::draw( void )
{
	if( m_bBackdrop )
		memcpy( HAPI->GetScreenPointer(), m_backdropColour, m_iWidth * m_iHeight * 4 );

	for( unsigned int i = 0; i < m_vSprite.size(); i++ )
		if( m_vSprite[i]->isActive() ) 
			m_vSprite[i]->draw( m_rect );
}

void CVisualisation::update( const int id, const int x, const int y, const int activeFrame, const int frameCount )
{
	m_vSprite[id]->setXY( x, y );
	m_vSprite[id]->setLastXY( x, y );
	m_vSprite[id]->setAnimation( activeFrame, frameCount );
}

void CVisualisation::lerp( const int id, const int newX, const int newY, const float s )
{
	int lastX = m_vSprite[id]->getLastX();
	int lastY = m_vSprite[id]->getLastY();

	int lerpX = (int)( lastX + ( s * ( newX - lastX ) ) );
	int lerpY = (int)( lastY + ( s * ( newY - lastY ) ) );

	m_vSprite[id]->setXY( lerpX, lerpY );
}

void CVisualisation::drawBox( const int x, const int y, const int w, const int h, HAPI_TColour col )
{
	for( int ty = y; ty < y + h; ty++ )
	{
		for( int tx = x; tx < x + w; tx++ )
		{
			int offset = ( tx + (ty * m_iWidth ) ) * 4;
			memcpy( HAPI->GetScreenPointer() + offset, &col, sizeof( col ) );
		}
	}
}

bool CVisualisation::createSprite( int &id, char *imageLocation, TDraw drawType )
{
	bool res = true;

	CSprite *newSprite = new CSprite();
	if( !newSprite->init( imageLocation, drawType ) )
		res = false;

	m_vSprite.push_back( newSprite );

	id = m_vSprite.size() - 1;

	return res;
}

bool CVisualisation::cloneSprite( int &id, int source_id )
{
	bool res = true;

	CSprite *newSprite = new CSprite();

	newSprite->copy( m_vSprite[source_id] );

	m_vSprite.push_back( newSprite );

	id = m_vSprite.size() - 1;

	return res;
}

void CVisualisation::setBackdropOn( const bool on )
{
	m_bBackdrop = on;
}

void CVisualisation::setBackdropColour( BYTE r, BYTE g, BYTE b )
{
	//populates a block of memory with the backdrop colour
	BYTE *tempPnt = m_backdropColour;

	for( int y = 0; y < m_iHeight; y++ )
	{
		for( int x = 0; x < m_iWidth; x++ )
		{
			tempPnt[0] = b;
			tempPnt[1] = g;
			tempPnt[2] = r;
			tempPnt[3] = 255;
			tempPnt += 4;
		}
	}
}
