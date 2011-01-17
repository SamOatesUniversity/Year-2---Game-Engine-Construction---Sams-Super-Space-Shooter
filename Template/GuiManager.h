#pragma once
#include "world.h"
#include "Sound_ids.h"

class CGuiMenu : public CWorldEntity
{
private:

public:
	CGuiMenu(void) { };
	~CGuiMenu(void) { };
	void init( void ) {
		m_iFrameCount = 4;
		m_iActiveFrame = 0;
		m_iWidth /= m_iFrameCount;
		m_iX = 144;
		m_iY = 44;
		m_side = TSideNeutral;
	}
	void setFrame( const int id ) { m_iActiveFrame = id; }
	virtual void update( void ) { };
	virtual void kill( void ) { };
};

class CGuiManager : public CWorldEntity
{
private:
	int m_iScore, m_iDifficulty;
	char sz_score[64];
	bool m_isMenu;
	CVisualisation *m_vis;
	CGuiMenu *m_menu;
public:
	CGuiManager(void);
	~CGuiManager(void);

	void init( CVisualisation *vis, CGuiMenu *menu );
	virtual void update( void );
	virtual void kill( void );

	void setScore( const int score ) { m_iScore = score; }
	void setHealth( const int health ) { m_iHealth = health; }

	bool inMenu( void ) { return m_isMenu; }
	const int getDifficulty( void ) { return m_iDifficulty; }
};

const bool isMouseInBox( const HAPI_TMouseData ms, const int x, const int y, const int w, const int h );