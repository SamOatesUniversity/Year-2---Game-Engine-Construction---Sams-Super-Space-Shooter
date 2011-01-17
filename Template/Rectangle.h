#pragma once

class CRectangle
{
private:
	//the actual position and size of the rectangle
	int x_, y_, w_, h_;
	//the last known clipped position and size
	int clipx1_, clipy1_, clipx2_, clipy2_;
	//the current position of the rectangle
	int posx_, posy_;
public:
	CRectangle( int x, int y, int w, int h );
	~CRectangle( void );
	bool isInDestination( CRectangle * destination );
	bool outOfDestination( CRectangle * destination );
	void clipTo( CRectangle *destination );

	const int getAbsoluteX( void ) { return x_; }
	const int getAbsoluteY( void ) { return y_; }
	const int getAbsoluteW( void ) { return w_; }
	const int getAbsoluteH( void ) { return h_; }

	const int getClipX1( void ) { return clipx1_; }
	const int getClipY1( void ) { return clipy1_; }
	const int getClipX2( void ) { return clipx2_; }
	const int getClipY2( void ) { return clipy2_; }

	void position( int x, int y ) { posx_ = x; posy_ = y; }
	void update( int x, int y, int w, int h );
};
