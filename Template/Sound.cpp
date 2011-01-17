#include "Sound.h"

CSound::CSound(void)
{
	BASS_Init( -1, 44100, 0, GetActiveWindow(), NULL ); 
}

CSound::~CSound(void)
{
}

void CSound::loadSound( int &id, char* soundLocation )
{
	HSAMPLE newSound = BASS_SampleLoad( FALSE, soundLocation, 0, 0, 100, NULL );
	m_soundId.push_back( newSound );
	id = m_soundId.size() - 1;
}

void CSound::playSound( int id )
{
	HCHANNEL channel = BASS_SampleGetChannel( m_soundId[id], FALSE );
	BASS_ChannelPlay( channel, FALSE );
}

void CSound::loopSound( int id )
{
	BASS_SAMPLE info;
	BASS_SampleGetInfo( m_soundId[id], &info );
	info.flags = BASS_SAMPLE_LOOP;
	BASS_SampleSetInfo( m_soundId[id], &info );
	HCHANNEL channel = BASS_SampleGetChannel( m_soundId[id], FALSE );
	BASS_ChannelPlay( channel, FALSE );
}
