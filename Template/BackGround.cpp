#include "BackGround.h"


CBackGround::CBackGround(void)
{
	m_side = TSideNeutral;
}

CBackGround::~CBackGround(void)
{
}

void CBackGround::update( void )
{
	m_iX++;
}

void CBackGround::kill( void )
{
}