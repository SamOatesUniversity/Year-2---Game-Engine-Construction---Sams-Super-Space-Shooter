#include "EmbededWebBrowser.h"

void CWebBrowser::LoadDLL( void )
{
	webdll_ = LoadLibrary("web.dll"); 
	if( webdll_ ) 
	{
		lpEmbedBrowserObject_ = (EmbedBrowserObjectPtr *)GetProcAddress((HINSTANCE)webdll_, "EmbedBrowserObject");
		lpUnEmbedBrowserObject_ = (UnEmbedBrowserObjectPtr *)GetProcAddress((HINSTANCE)webdll_, "UnEmbedBrowserObject");
		lpDisplayHTMLPage_ = (DisplayHTMLPagePtr *)GetProcAddress((HINSTANCE)webdll_, "DisplayHTMLPage");

		if( !lpEmbedBrowserObject_ || !lpUnEmbedBrowserObject_ || !lpDisplayHTMLPage_ )
			MessageBox( GetActiveWindow(), "Could Not Load \"Web.dll\"", "WebBrowser Error", MB_OK );
	}	
	else
	{
		MessageBox( GetActiveWindow(), "Could Not Load \"Web.dll\"", "WebBrowser Error", MB_OK );
	}
}

BOOL CALLBACK WebBrowserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if(message == WM_SIZE) {
		HWND br = FindWindowEx(hwnd, NULL,NULL,NULL);
		if(br){
			MoveWindow(br,0,0,LOWORD(lParam),HIWORD(lParam),true);
			UpdateWindow(br);                 
		}               
	}	
	return 0; 
}

void CWebBrowser::Create( void )
{
	webdll_ = NULL;
	LoadDLL();
	this->parent_ = GetActiveWindow();
	browser_ = CreateWindowEx( NULL, WC_DIALOG, NULL,
							  WS_CHILD | WS_CLIPCHILDREN | WS_DISABLED,
							  0, 0, 400, 300, parent_, NULL, NULL, NULL );
	if( browser_ )
	{
		SetWindowLongPtr( parent_, GWL_STYLE, GetWindowLongPtr( parent_, GWL_STYLE ) | WS_CLIPCHILDREN );
		SetWindowLong( browser_, DWL_DLGPROC, (long)WebBrowserProc );   
		if( (*lpEmbedBrowserObject_)(browser_) ) return;
		this->Visable( false );
	}  
}

CWebBrowser::CWebBrowser( void )
{
}

CWebBrowser::~CWebBrowser( void )
{
	(*lpUnEmbedBrowserObject_)(browser_);
	if( webdll_ ) FreeLibrary( webdll_ );
}

void CWebBrowser::NavigateTo( char* url )
{
	(*lpDisplayHTMLPage_)( browser_, (LPCTSTR)url );
}

void CWebBrowser::Resize( int w, int h )
{
	MoveWindow( browser_, 0, 0, w, h, true );
	UpdateWindow( browser_ ); 	
}

void CWebBrowser::Position(int x, int y)
{
	RECT rcWindow;
	GetWindowRect( browser_, &rcWindow);
	MoveWindow( browser_, x, y, x + rcWindow.right, y + rcWindow.bottom, true );
	UpdateWindow( browser_ );
}

void CWebBrowser::FitToWindow( void )
{
	RECT rcWindow;
	GetClientRect( parent_, &rcWindow );
	MoveWindow( browser_, 0, 0, rcWindow.right, rcWindow.bottom, true );
	UpdateWindow( browser_ ); 
}

void CWebBrowser::Visable( bool visable )
{
	if( !visable )
	{
		EnableWindow( browser_, FALSE );
		ShowWindow( browser_, SW_HIDE );
		isVisable_ = false;
	}
	else
	{
		EnableWindow( browser_, TRUE );
		SetWindowLongPtr( browser_, GWL_STYLE, GetWindowLongPtr( browser_, GWL_STYLE ) | WS_VISIBLE );
		ShowWindow( browser_, SW_SHOW );
		isVisable_ = true;
	}
}

bool CWebBrowser::isVisable( void )
{
	return this->isVisable_;
}