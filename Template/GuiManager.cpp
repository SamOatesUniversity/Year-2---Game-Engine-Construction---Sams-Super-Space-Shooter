#include "GuiManager.h"

CGuiManager::CGuiManager(void)
{
	m_isMenu = true;
	m_iDifficulty = 0;
}

CGuiManager::~CGuiManager(void)
{
	CSound::Instance().stopSound( soundAmbient );
}

void CGuiManager::init( CVisualisation *vis, CGuiMenu *menu )
{
	m_vis = vis;
	m_iY = m_iScreenHeight - m_iHeight;
	HAPI->ChangeFont( "Arial", 30, 30 );
	CSound::Instance().loopSound( soundAmbient );

	m_menu = menu;
	m_menu->init();
}

void CGuiManager::update( void )
{
	sprintf_s( sz_score, "%d", m_iScore );
	HAPI->RenderText( 204, 570, HAPI_TColour( 255, 255, 255 ), sz_score );

	m_vis->drawBox( 206, m_iScreenHeight - m_iHeight + 4, 498 - ( ( 100 - m_iHealth ) * 5 ), 25, HAPI_TColour( 120, 0, 0 ) );

	if( m_iHealth <= 0 )
	{
		m_isMenu = true;
		m_iDifficulty = 0;
		m_menu->position( 144, 44 );
	}
	
	if( m_isMenu )
	{
		HAPI_TMouseData ms;
		HAPI->GetMouseData( &ms ); 
		
		m_menu->setFrame( 0 );

		//easy
		if( isMouseInBox( ms, 144 + 92, 44 + 86, 330, 100 ) )
			if( ms.leftButtonDown )
				m_iDifficulty = 1;
			else
				m_menu->setFrame( 1 );

		//medium
		if( isMouseInBox( ms, 144 + 30, 44 + 206, 452, 100 ) )
			if( ms.leftButtonDown )
				m_iDifficulty = 2;
			else
				m_menu->setFrame( 2 );

		//hard
		if( isMouseInBox( ms, 144 + 84, 44 + 316, 342, 100 ) )
			if( ms.leftButtonDown )
				m_iDifficulty = 4;
			else
				m_menu->setFrame( 3 );

		m_isMenu = m_iDifficulty != 0 ? false : true;
		if( !m_isMenu ) m_menu->position( m_iScreenWidth, 0 );
	}
}
void CGuiManager::kill( void )
{

}

const bool isMouseInBox( const HAPI_TMouseData ms, const int x, const int y, const int w, const int h )
{
	bool res = false;

	if( ms.x >= x && ms.x <= x + w && ms.y >= y && ms.y <= y + h ) 
		res = true;

	return res;
}

