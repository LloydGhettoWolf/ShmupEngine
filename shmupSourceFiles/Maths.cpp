#include "Maths.h"

namespace Advanced2D
{
	float Math::ToDegrees(float radian)
	{
		return radian * PI_UNDER_180;
	}

	float Math::ToRadians(float degrees)
	{
		return degrees * PI_OVER_180;
	}

	float Math::WrapAngleRadians(float radians)
	{
		float result = fmod(radians,PI*2.0f);
		if(result < 0.0f) result += 2.0f * PI;
		return result;
	}

	float Math::WrapAngleDegrees(float degrees)
	{
		float result = fmod(degrees,360.0f);
		if(result < 0.0f) result += 360.0f;
		return result;
	}

	float Math::LinearVelocityX(float angle)
	{
		angle -= 90.0f;
		if(angle < 0) angle += 360.0f;
		return cos(angle * PI_OVER_180);
	}

	float Math::LinearVelocityY(float angle)
	{
		angle -= 90.0f;
		if(angle < 0) angle += 360.0f;
		return sin(angle * PI_OVER_180);
	}

	Vector2 Math::LinearVelocity(float angle)
	{
		float fX = LinearVelocityX(angle);
		float fY = LinearVelocityY(angle);
		return Vector2(fX,fY);
	}

	float Math::AngleToTarget(float x1,float y1,float x2,float y2)
	{
		float deltaX = x2-x1;
		float deltaY = y2-y1;
		return atan2(deltaX,deltaY);
	}

	float Math::AngleToTarget(const Vector2& vec1,const Vector2& vec2)
	{
		return AngleToTarget(vec1.GetX(),vec1.GetY(),vec2.GetX(),vec2.GetY());
	}

	float Math::Distance(float x1,float y1,float x2,float y2)
	{
		float deltaX = x2-x1;
		float deltaY = y2-y1;
		return sqrt((deltaX*deltaX)+(deltaY*deltaY));
	}

	float Math::Distance(const Vector2& vec1,const Vector2& vec2)
	{
		return Distance(vec1.GetX(),vec1.GetY(),vec2.GetX(),vec2.GetY());
	}

	float Math::Length(float x1,float y1)
	{
		return sqrt(x1*x1 + y1*y1);
	}

	float Math::Length(const Vector2& vec)
	{
		return Length(vec.GetX(),vec.GetY());
	}

	float Math::DotProduct(float x1,float y1,float x2,float y2)
	{
		return (x1*x2 + y1*y2);
	}

	float Math::DotProduct(const Vector2& vec1,const Vector2& vec2)
	{
		return DotProduct(vec1.GetX(),vec1.GetY(),vec2.GetX(),vec2.GetY());
	}


	Vector2 Math::Normalise(float x,float y)
	{
		float length = Length(x,y);
		if(length != 0 ) length = 1/length;
		float nx = length * x;
		float ny = length * y;
		return Vector2(nx,ny);
	}

	Vector2 Math::Normalise(const Vector2& vec)
	{
		return Normalise(vec.GetX(),vec.GetY());
	}

};