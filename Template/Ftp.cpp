#include "Ftp.h"

bool FileExists( char* fileName )
{
	return ( GetFileAttributes( fileName ) != 0xFFFFFFFF );
}

bool FTP_Download( FTP_Details ftp, char* remotename, char* localname, char* remote_dir )
{
	std::string str, dir;
	char message[256];
	
	HINTERNET hOpen = InternetOpen( "FTP Download", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if( !hOpen )
	{
		MessageBox( GetActiveWindow(), "File could not be found, The application will now exit", "Missing File Error", MB_OK | MB_ICONHAND );
		return false;
	}

    HINTERNET hConnect = InternetConnect( hOpen, ftp.servername, ftp.port,
                                ftp.username, ftp.password, INTERNET_SERVICE_FTP,
                                INTERNET_FLAG_PASSIVE, 0 );
    if( !hConnect )
	{
		MessageBox( GetActiveWindow(), "File could not be found, The application will now exit", "Missing File Error", MB_OK | MB_ICONHAND );
		return false;
	}

	char remdir[255];
	strcpy_s( remdir, ftp.directory );
	strcat_s( remdir, remote_dir );
	FtpSetCurrentDirectory( hConnect, remdir );

	str = localname;
	if( str.find( "/" ) ) dir = str.substr( 0, str.find( "/" ) );
	if( !FileExists( (char*)dir.c_str() ) ) CreateDirectory( (char*)dir.c_str(), NULL );

	sprintf_s( message, "Could not find file '%s'\nNow attempting to download the file.", remotename );
	MessageBox( GetActiveWindow(), message, "Missing File Error", MB_OK | MB_ICONEXCLAMATION );

	BOOL lRes = FtpGetFile( hConnect, remotename, localname, false,
                            FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 0 );
    if( !lRes )
	{
		MessageBox( GetActiveWindow(), "File could not be downloaded, The application will now exit", "Missing File Error", MB_OK | MB_ICONHAND );
		return false;
	}

	InternetCloseHandle( hConnect );
	InternetCloseHandle( hOpen );

	MessageBox( GetActiveWindow(), "File sucessfully downloaded", "Missing File Error", MB_OK | MB_ICONASTERISK );

	return true;
}