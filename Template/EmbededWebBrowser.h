//////////////////////////////////
// DGDK WebBrowser Header File  //
//     Created By N3wton        //
//////////////////////////////////

#pragma once

#include <Windows.h>
#include <tchar.h>

class WebBrowser {
private:
	HWND browser_, parent_;	
	bool isVisable_;
public:
	WebBrowser( char* url, int x = 0, int y = 0, int w = 640, int h = 480, bool visable = true );
	~WebBrowser( void );
	void NavigateTo( char* url );
	void Resize( int w, int h );
	void Position( int x, int y );
	void FitToWindow( void );
	void Visable( bool visable );
	bool isVisable( void );
	HWND hWnd( void );
};