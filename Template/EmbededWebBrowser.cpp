#include "EmbededWebBrowser.h"

typedef long WINAPI EmbedBrowserObjectPtr(HWND);
typedef long WINAPI UnEmbedBrowserObjectPtr(HWND);
typedef long WINAPI DisplayHTMLPagePtr(HWND, LPCTSTR);
typedef long WINAPI DisplayHTMLStrPtr(HWND, LPCTSTR);

BOOL CALLBACK WebBrowserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

static void LoadDLL( void );
static HINSTANCE					webdll_; 
static bool							dll_loaded_;
static int							browser_count_;
static EmbedBrowserObjectPtr		*lpEmbedBrowserObject_;
static UnEmbedBrowserObjectPtr		*lpUnEmbedBrowserObject_;
static DisplayHTMLPagePtr			*lpDisplayHTMLPage_;

void LoadDLL( void )
{
	if(dll_loaded_) return;

	browser_count_ = 0;

	webdll_ = LoadLibrary("web.dll"); 
	if( webdll_ ) 
	{
		lpEmbedBrowserObject_ = (EmbedBrowserObjectPtr *)GetProcAddress((HINSTANCE)webdll_, "EmbedBrowserObject");
		lpUnEmbedBrowserObject_ = (UnEmbedBrowserObjectPtr *)GetProcAddress((HINSTANCE)webdll_, "UnEmbedBrowserObject");
		lpDisplayHTMLPage_ = (DisplayHTMLPagePtr *)GetProcAddress((HINSTANCE)webdll_, "DisplayHTMLPage");

		if( !lpEmbedBrowserObject_ || !lpUnEmbedBrowserObject_ || !lpDisplayHTMLPage_ )
		return;

		dll_loaded_=true;
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

WebBrowser::WebBrowser( char* url, int x, int y, int w, int h, bool visable )
{
	LoadDLL();
	this->parent_ = GetActiveWindow();
	browser_ = CreateWindowEx( NULL, WC_DIALOG, NULL,
							  WS_CHILD | WS_CLIPCHILDREN,
							  x, y, w, h, parent_, NULL, NULL, NULL );
	//WS_VISIBLE
	if( browser_ )
	{
		SetWindowLongPtr( parent_, GWL_STYLE, GetWindowLongPtr( parent_, GWL_STYLE ) | WS_CLIPCHILDREN );
		SetWindowLong( browser_, DWL_DLGPROC, (long)WebBrowserProc );   
		if( (*lpEmbedBrowserObject_)(browser_) ) return;
		this->NavigateTo( url );
		this->Visable( visable );
		browser_count_++;
	}  
}

WebBrowser::~WebBrowser( void )
{
	if( browser_ )(*lpUnEmbedBrowserObject_)(browser_);
	if( dll_loaded_ && browser_count_ == 1 )
	{
		FreeLibrary( webdll_ );
		dll_loaded_ = false;
	}
	browser_count_--;
}

void WebBrowser::NavigateTo( char* url )
{
	(*lpDisplayHTMLPage_)( browser_, (LPCTSTR)url );
}

void WebBrowser::Resize( int w, int h )
{
	MoveWindow( browser_, 0, 0, w, h, true );
	UpdateWindow( browser_ ); 	
}

void WebBrowser::Position(int x, int y)
{
	RECT rcWindow;
	GetWindowRect( browser_, &rcWindow);
	MoveWindow( browser_, x, y, x + rcWindow.right, y + rcWindow.bottom, true );
	UpdateWindow( browser_ );
}

void WebBrowser::FitToWindow( void )
{
	RECT rcWindow;
	GetClientRect( parent_, &rcWindow );
	MoveWindow( browser_, 0, 0, rcWindow.right, rcWindow.bottom, true );
	UpdateWindow( browser_ ); 
}

void WebBrowser::Visable( bool visable )
{
	if( !visable )
	{
		ShowWindow( browser_, SW_HIDE );
		isVisable_ = false;
	}
	else
	{
		SetWindowLongPtr( browser_, GWL_STYLE, GetWindowLongPtr( browser_, GWL_STYLE ) | WS_VISIBLE );
		ShowWindow( browser_, SW_SHOW );
		isVisable_ = true;
	}
}

bool WebBrowser::isVisable( void )
{
	return this->isVisable_;
}

HWND WebBrowser::hWnd( void )
{
	return this->browser_;
}