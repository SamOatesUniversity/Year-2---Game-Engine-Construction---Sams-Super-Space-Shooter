#pragma once

#include "worldentity.h"

class CEnemyBullet : public CWorldEntity
{
public:
	CEnemyBullet(void);
	~CEnemyBullet(void);
	void init( void );

	virtual void update( void );
	virtual void kill( void );

	void fire( const int x, const int y );
};

