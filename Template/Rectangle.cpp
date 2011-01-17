#include "Rectangle.h"


CRectangle::CRectangle( int x, int y, int w, int h )
{
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
	clipx1_ = x_;
	clipy1_ = y_;
	clipx2_ = x_ + w_;
	clipy2_ = y_ + h_;
	posx_ = 0;
	posy_ = 0;
}

CRectangle::~CRectangle( void )
{

}

bool CRectangle::isInDestination( CRectangle *destination )
{
	const int destX1 = destination->getAbsoluteX();
	const int destY1 = destination->getAbsoluteY();
	const int destX2 = destX1 + destination->getAbsoluteW();
	const int destY2 = destY1 + destination->getAbsoluteH();

	return ( (posx_ >= destX1) && (posx_ + w_ <= destX2) && (posy_ >= destY1) && (posy_ + h_ <= destY2) );
}

bool CRectangle::outOfDestination( CRectangle *destination )
{
	const int destX1 = destination->getAbsoluteX();
	const int destY1 = destination->getAbsoluteY();
	const int destX2 = destX1 + destination->getAbsoluteW();
	const int destY2 = destY1 + destination->getAbsoluteH();

	return ( (posx_ + w_ < destX1) || (posx_ > destX2) || (posy_ + h_ < destY1) || (posy_ > destY2) );
}

void CRectangle::clipTo( CRectangle *destination )
{
	//if its fully in the destination, don't clip, so exit and send indestination flag
	bool inDest = isInDestination( destination );
	//if its fully out of the destination, don't clip, so exit and send outdestination flag.
	bool outDest = outOfDestination( destination );

	if( !inDest || !outDest )
	{
		//get x, y, w, h of the destination and temp store them
		const int destX1 = destination->getAbsoluteX();
		const int destY1 = destination->getAbsoluteY();
		const int destX2 = destX1 + destination->getAbsoluteW();
		const int destY2 = destY1 + destination->getAbsoluteH();

		//update the clip coordinates into destination space
		clipx1_ = x_ + posx_;
		clipy1_ = y_ + posy_;
		clipx2_ = x_ + w_ + posx_;
		clipy2_ = y_ + h_ + posy_;

		//clip the rectangle
		if( clipx1_ < destX1 ) clipx1_ = destX1;
		if( clipy1_ < destY1 ) clipy1_ = destY1;
		if( clipx2_ > destX2 ) clipx2_ = destX2;
		if( clipy2_ > destY2 ) clipy2_ = destY2;

		//convert back into souce space
		clipx1_ -= posx_;
		clipy1_ -= posy_;
		clipx2_ -= posx_;
		clipy2_ -= posy_;
	}
}

void CRectangle::update( int x, int y, int w, int h )
{
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
	clipx1_ = x_;
	clipy1_ = y_;
	clipx2_ = x_ + w_;
	clipy2_ = y_ + h_;
}