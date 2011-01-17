#include "World.h"
#include "Explosion.h"
#include "EnemyBullet.h"

class CEnemyLarge : public CWorldEntity
{
private:
	float m_Offset, m_fireTimer;
	bool m_attack;
	CExplosion *m_explosion;
	std::vector<CEnemyBullet*> m_bullet;
	int m_iActiveBullet, m_iBulletCount;
public:
	CEnemyLarge(void);
	~CEnemyLarge(void);
	void init( const int offset );
	void reset( void );

	virtual void update( void );
	virtual void kill( void );

	CExplosion *getExplosion( void ) { return m_explosion; }
	CEnemyBullet *getBullet( const int id ) { return m_bullet[id]; }

	const int getBulletCount( void ) { return m_iBulletCount; }

	void setOffset( const int offset ) { m_Offset = offset * 0.5f; m_iX = m_iScreenWidth + ( ( m_iWidth * 2 ) * offset ); }
};

void createLargeEnemy( CEnemyLarge *enemy, CExplosion *explosion, CWorld *world );
void createLargeEnemy( CEnemyLarge *enemy, CEnemyLarge *source, CExplosion *explosion, CWorld *world );
