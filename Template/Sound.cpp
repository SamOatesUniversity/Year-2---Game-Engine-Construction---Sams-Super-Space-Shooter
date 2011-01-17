#include "Sound.h"

CSound::CSound(void)
{
}

CSound::~CSound(void)
{
}

void CSound::loadSound( int &id, char* soundLocation )
{
	HAPI->LoadSound( soundLocation, &id );
	m_sound.push_back( soundLocation );
	m_soundId.push_back( id );
	id = m_sound.size() - 1;
}

void CSound::playSound( int id )
{
	HAPI->PlayStreamedMedia( m_sound[id] );
}

void CSound::loopSound( int id )
{
	HAPI->PlayASound( m_soundId[1], true );
}
