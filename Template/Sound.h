#pragma once

#include "bass.h"
#include <Windows.h>
#include <HAPI_lib.h>
#include <vector>

class CSound
{
private:
	CSound( void );
	~CSound( void );
	CSound( CSound const& );
	CSound& operator = ( CSound const& );
	std::vector<HSAMPLE> m_soundId;
public:
	static CSound& Instance( void )
	{
		static CSound sound;
		return sound;
	}

	void loadSound( int &id, char* soundLocation );
	void playSound( int id );
	void loopSound( int id );
	void stopSound( int id );
};

