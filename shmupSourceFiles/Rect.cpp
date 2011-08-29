//rect.cpp
#include "Rect.h"

namespace Advanced2D
{
	Rect::Rect(float left,float top,float width,float height)
	{
		this->vals[0][0]   = left;
		this->vals[1][0]   = left + width;
		this->vals[0][1]   = top;
		this->vals[1][1]   = top + height;
	}

	bool Rect::TestIntersect(Rect& rect2)
	{
		if(vals[1][0] < rect2.vals[0][0]) return false;
		if(vals[0][0] > rect2.vals[1][0]) return false;
		if(vals[1][1] < rect2.vals[0][1]) return false;
		if(vals[0][1] > rect2.vals[1][1]) return false;

		return true;
	}

};