#pragma once

#include "WorldEntity.h"

class CBackGround : public CWorldEntity
{
public:
	CBackGround(void);
	~CBackGround(void);

	virtual void update( void );
	virtual void kill( void );
};

