#pragma once
#include <vector>
#include "EnemySmall.h"
#include "EnemyMedium.h"
#include "EnemyLarge.h"

class CAiManger
{
private:
	float m_SmallAttackTimer, m_MediumAttackTimer, m_LargeAttackTimer;
	int m_iSmallEnemyCount, m_iMediumEnemyCount, m_iLargeEnemyCount;
	bool m_smallAttack, m_mediumAttack, m_largeAttack;
	std::vector<CEnemySmall*> m_smallEnemys;
	std::vector<CEnemyMedium*> m_mediumEnemys;
	std::vector<CEnemyLarge*> m_largeEnemys;
public:
	CAiManger(void);
	~CAiManger(void);
	void init( CExplosion *explosion, CWorld *world );
	void reset( void );

	void update( int difficulty );

	void LaunchSmallAttack( void );
	void LaunchMediumAttack( void );
	void LaunchLargeAttack( void );
};

