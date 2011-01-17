#pragma once
#include <vector>
#include "Sprite.h"

class CVisualisation
{
private:
	int m_iWidth, m_iHeight;
	bool m_bBackdrop;
	std::vector<CSprite*> m_vSprite;
	CRectangle *m_rect;
	BYTE *m_backdropColour;
public:
	CVisualisation(void);
	~CVisualisation(void);
	bool init( int width, int height );
	void draw( void );
	void update( const int id, const int x, const int y, const int activeFrame, const int frameCount );
	void lerp( const int id, const int x, const int y, const float s );

	void drawBox( const int x, const int y, const int w, const int h, HAPI_TColour col ); 

	bool createSprite( int &id, char *imageLocation, TDraw drawType );
	bool cloneSprite( int &id, int source_id );

	void setBackdropColour( BYTE r, BYTE g, BYTE b );
	void setBackdropOn( const bool on );

	const int getWidth( const int id ) { return m_vSprite[id]->getWidth(); }
	const int getHeight( const int id ) { return m_vSprite[id]->getHeight(); }

	void setActive( const int id, const bool active ) { m_vSprite[id]->setActive( active ); }

	CRectangle *getScreenRect( void ) { return m_rect; }
};

