//Rect.h - simple rectangle class for use as an AABB
#pragma once

namespace Advanced2D
{
	class Rect
	{
		public:
			Rect(){};
			Rect(float left,float top,float width,float height);
			virtual ~Rect(){};

			bool TestIntersect(Rect& rect2);

			//a 2x2 array of min and max x/y vals where 1st dimension is min/max and the 2nd is
			//x/y
			float vals[2][2];
			unsigned int boxID;
			unsigned int objID;
			unsigned int type;
	};
};