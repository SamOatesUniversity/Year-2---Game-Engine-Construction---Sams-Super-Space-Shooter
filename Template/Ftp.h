#include <Windows.h>
#include <wininet.h>
#include <stdio.h>
#include <string>

#pragma comment ( lib, "Wininet.lib" )

struct FTP_Details {
    LPCSTR servername;
    INTERNET_PORT port;
    LPCSTR username;
    LPCSTR password;
	LPCSTR directory;
};

bool FileExists( char* fileName );

bool FTP_Download( FTP_Details ftp, char* remotename, char* localname, char* remote_dir );

