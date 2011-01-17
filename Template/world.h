#pragma once
#include "Visualisation.h"
#include "WorldEntity.h"
#include "Ftp.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class CWorld
{
private:
	CVisualisation *m_vis;
	std::vector<CWorldEntity*> m_vEntity;
	float m_coreTimer, m_tickRate;
	int m_iScreenWidth, m_iScreenHeight;
	FTP_Details m_ftpDetails;
public:
	CWorld(void);
	~CWorld(void);
	bool init( int width, int height );
	void update( void );

	void setFtpDetails( char* server_address, char* username, char* password, char *directory );

	bool addEntity( CWorldEntity *entity, char *imageLocation, TDraw drawType = Tnormal );
	bool cloneEntity( CWorldEntity *source_entity, CWorldEntity *entity );

	bool addSound( int &id, char *soundLocation );

	CVisualisation *visualisation( void ) { return m_vis; }
};