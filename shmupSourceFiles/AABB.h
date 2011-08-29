//AABB - a specialised type of rect - has an object id tied to its entity owner and a 'type' too for collision map lookup
#pragma once

#include "Rect.h"

namespace Advanced2D
{
	class AABB : public Rect
	{
		public:
			AABB() {};
			AABB(int type,unsigned int id,int left,int top,int right,int bottom) : Rect(left,top,right,bottom) {}
			~AABB() {};

			unsigned int objId;
			int objectType;
	};
};