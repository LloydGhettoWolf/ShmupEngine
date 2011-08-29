//maths.h - utility functions for maths style stuff 
//Last Update 15/08/2011

#pragma once
#include "Includes.h"
#include "Vector2.h"

namespace Advanced2D
{
	const float PI = 3.14159f;
	const float PI_OVER_180 = PI/ 180.0f;
	const float PI_UNDER_180 = 180.0f/PI;

	class Math
	{

		public:
			static float ToDegrees(float radian);
			static float ToRadians(float degrees);
			static float WrapAngleDegrees(float degrees);
			static float WrapAngleRadians(float radians);
			static float LinearVelocityX(float angle);
			static float LinearVelocityY(float angle);
			static Vector2 LinearVelocity(float angle);
			static float AngleToTarget(float x1,float y1,float x2,float y2);
			static float AngleToTarget(const Vector2& pt1,const Vector2& pt2);
			static float Distance(float x1,float y1,float x2,float y2);
			static float Distance(const Vector2& pt1,const Vector2& pt2);
			static float Length(const Vector2& vec);
			static float Length(float x,float y);
			static float DotProduct(const Vector2& vec1,const Vector2& vec2);
			static float DotProduct(float x1,float y1,float x2,float y2);
			static Vector2 Normalise(float x,float y);
			static Vector2 Normalise(const Vector2& vec);
		
	};
};