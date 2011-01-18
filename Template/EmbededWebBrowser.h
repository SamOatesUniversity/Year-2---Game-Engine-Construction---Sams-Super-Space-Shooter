#pragma once

#include <Windows.h>

typedef long WINAPI EmbedBrowserObjectPtr(HWND);
typedef long WINAPI UnEmbedBrowserObjectPtr(HWND);
typedef long WINAPI DisplayHTMLPagePtr(HWND, LPCTSTR);
typedef long WINAPI DisplayHTMLStrPtr(HWND, LPCTSTR);

BOOL CALLBACK WebBrowserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class CWebBrowser
{
private:
	CWebBrowser( void );
	~CWebBrowser( void );
	CWebBrowser( CWebBrowser const& );
	CWebBrowser& operator = ( CWebBrowser const& );

	void LoadDLL( void );

	HWND browser_, parent_;	
	bool isVisable_;
	HINSTANCE webdll_; 
	EmbedBrowserObjectPtr *lpEmbedBrowserObject_;
	UnEmbedBrowserObjectPtr *lpUnEmbedBrowserObject_;
	DisplayHTMLPagePtr *lpDisplayHTMLPage_;
public:
	static CWebBrowser& Instance( void )
	{
		static CWebBrowser browser;
		return browser;
	}

	void Create( void );
	void NavigateTo( char* url );
	void Resize( int w, int h );
	void Position( int x, int y );
	void FitToWindow( void );
	void Visable( bool visable );
	bool isVisable( void );
};