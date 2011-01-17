#include "AiManger.h"

CAiManger::CAiManger(void)
{
	m_iSmallEnemyCount = 16;
	for( int i = 0; i < m_iSmallEnemyCount; i++ ) m_smallEnemys.push_back( new CEnemySmall() );
	m_smallAttack = false;
	m_SmallAttackTimer = (float)HAPI->GetTime();

	m_iMediumEnemyCount = 12;
	for( int i = 0; i < m_iMediumEnemyCount; i++ ) m_mediumEnemys.push_back( new CEnemyMedium() );
	m_mediumAttack = false;
	m_MediumAttackTimer = (float)HAPI->GetTime();

	m_iLargeEnemyCount = 8;
	for( int i = 0; i < m_iLargeEnemyCount; i++ ) m_largeEnemys.push_back( new CEnemyLarge() );
	m_largeAttack = false;
	m_LargeAttackTimer = (float)HAPI->GetTime();
}

CAiManger::~CAiManger(void)
{
}

void CAiManger::init( CExplosion *explosion, CWorld *world )
{
	createSmallEnemy( m_smallEnemys[0], explosion, world );
	for( int i = 1; i < m_iSmallEnemyCount; i++ )
		createSmallEnemy( m_smallEnemys[i], m_smallEnemys[0], explosion, world );

	createMediumEnemy( m_mediumEnemys[0], explosion, world );
	for( int i = 1; i < m_iMediumEnemyCount; i++ )
		createMediumEnemy( m_mediumEnemys[i], m_mediumEnemys[0], explosion, world );

	createLargeEnemy( m_largeEnemys[0], explosion, world );
	for( int i = 1; i < m_iLargeEnemyCount; i++ )
		createLargeEnemy( m_largeEnemys[i], m_largeEnemys[0], explosion, world );
}

void CAiManger::reset( void )
{
	m_SmallAttackTimer = (float)HAPI->GetTime();
	m_MediumAttackTimer = (float)HAPI->GetTime();
	m_LargeAttackTimer = (float)HAPI->GetTime();
	m_smallAttack = false;
	m_mediumAttack = false;
	m_largeAttack = false;

	for( int i = 0; i < m_iSmallEnemyCount; i++ )
	{
		m_smallEnemys[i]->setActive( false );
		m_smallEnemys[i]->position( 800, 0 );
		m_smallEnemys[i]->reset();
	}

	for( int i = 0; i < m_iMediumEnemyCount; i++ )
	{
		m_mediumEnemys[i]->setActive( false );
		m_mediumEnemys[i]->position( 800, 0 );
		m_mediumEnemys[i]->reset();
	}

	for( int i = 0; i < m_iLargeEnemyCount; i++ )
	{
		m_largeEnemys[i]->setActive( false );
		m_largeEnemys[i]->position( 800, 0 );
		m_largeEnemys[i]->reset();
	}
}

void CAiManger::update( int difficulty )
{
	if( !m_smallAttack && (float)HAPI->GetTime() - m_SmallAttackTimer > ( 4000 / difficulty ) )
	{
		m_smallAttack = true;
		LaunchSmallAttack();
	}
	else if( m_smallAttack )
	{
		bool alldead = true;
		for( int i = 0; i < m_iSmallEnemyCount; i++ ) if( m_smallEnemys[i]->isActive() ) alldead = false;
		if( alldead )
		{
			m_SmallAttackTimer = (float)HAPI->GetTime();
			m_smallAttack = false;
		}
	}

	if( !m_mediumAttack && (float)HAPI->GetTime() - m_MediumAttackTimer > ( 8000 / difficulty ) )
	{
		m_mediumAttack = true;
		LaunchMediumAttack();
	}
	else if( m_mediumAttack )
	{
		bool alldead = true;
		for( int i = 0; i < m_iMediumEnemyCount; i++ ) if( m_mediumEnemys[i]->isActive() ) alldead = false;
		if( alldead )
		{
			m_MediumAttackTimer = (float)HAPI->GetTime();
			m_mediumAttack = false;
		}
	}

	if( !m_largeAttack && (float)HAPI->GetTime() - m_LargeAttackTimer > ( 12000 / difficulty ) )
	{
		m_largeAttack = true;
		LaunchLargeAttack();
	}
	else if( m_largeAttack )
	{
		bool alldead = true;
		for( int i = 0; i < m_iLargeEnemyCount; i++ ) if( m_largeEnemys[i]->isActive() ) alldead = false;
		if( alldead )
		{
			m_LargeAttackTimer = (float)HAPI->GetTime();
			m_largeAttack = false;
		}
	}
}

void CAiManger::LaunchSmallAttack( void )
{
	for( int i = 0; i < m_iSmallEnemyCount; i++ )
	{
		m_smallEnemys[i]->setActive( true );
		m_smallEnemys[i]->setOffset( i );
	}
}

void CAiManger::LaunchMediumAttack( void )
{
	for( int i = 0; i < m_iMediumEnemyCount; i++ )
	{
		m_mediumEnemys[i]->setActive( true );
		m_mediumEnemys[i]->setOffset( i );
	}
}

void CAiManger::LaunchLargeAttack( void )
{
	for( int i = 0; i < m_iLargeEnemyCount; i++ )
	{
		m_largeEnemys[i]->setActive( true );
		m_largeEnemys[i]->setOffset( i );
	}
}