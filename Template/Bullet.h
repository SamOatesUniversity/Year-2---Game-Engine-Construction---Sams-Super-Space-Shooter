#pragma once
#include "worldentity.h"

class CBullet : public CWorldEntity
{
private:
	bool m_hitEnemy;
public:
	CBullet(void);
	~CBullet(void);
	void init( void );

	virtual void update( void );
	virtual void kill( void );

	void fire( const int x, const int y );

	bool hitEnemy( void ) { bool val = m_hitEnemy; m_hitEnemy = false; return val; }

	void reset( void )
	{
		m_iX = -m_iWidth;
		m_hitEnemy = false;
	}
};
