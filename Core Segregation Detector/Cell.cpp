#include "Cell.h"


Cell::Cell()
{
	x = y = xSpan = ySpan = value = 0;
	active = false;
	automatonActive = true;
}


Cell::~Cell()
{
}

void Cell::setDistanceToCenter(double distanceTocenter)
{
	this->distanceToCenter = distanceTocenter;
}
