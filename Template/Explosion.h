#pragma once
#include "world.h"
#include "Sound_ids.h"

class CExplosion : public CWorldEntity
{
public:
	CExplosion(void);
	~CExplosion(void);

	void init( void );

	virtual void update( void );
	virtual void kill( void );
};