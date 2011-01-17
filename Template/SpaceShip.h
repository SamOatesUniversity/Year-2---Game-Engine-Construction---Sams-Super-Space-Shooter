#pragma once
#include "World.h"
#include "Bullet.h"
#include "Explosion.h"
#include "EmbededWebBrowser.h"

class CSpaceShip : public CWorldEntity
{
private:
	float m_Speed, m_Turn, m_fireTimer;
	std::vector<CBullet*> m_bullet;
	int m_iActiveBullet, m_iBulletCount, m_iScore, m_iDifficulty;
	bool m_rightWingBullet;
	CExplosion *m_explosion;
	WebBrowser *m_web;
public:
	CSpaceShip(void);
	~CSpaceShip(void);

	void init( void );

	virtual void update( void );
	virtual void kill( void );

	CExplosion *getExplosion( void ) { return m_explosion; }
	CBullet *getBullet( const int id ) { return m_bullet[id]; }

	const int getBulletCount( void ) { return m_iBulletCount; }

	const int getScore( void ) { return m_iScore; }

	void setDifficulty( const int difficulty ) { m_iDifficulty = difficulty; }

	void restart( void );
};

void createSpaceShip( CSpaceShip *spaceShip, CExplosion *explosion, CWorld *world );
