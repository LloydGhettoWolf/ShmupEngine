#include "Vector2.h"

namespace Advanced2D
{
	Vector2::Vector2()
	{
		x = y = 0;
	}

	Vector2::Vector2(const Vector2& v)
	{
		x = v.GetX();
		y = v.GetY();
	}

	Vector2::Vector2(float valueX,float valueY): x(valueX),y(valueY){};

	Vector2::Vector2(int valueX,int valueY)
	{
		x = (float)valueX;
		y = (float)valueY;
	}

	void Vector2::Set(const Vector2& v)
	{
		x = v.GetX();
		y = v.GetY();
	}

	void Vector2::Set(float valueX,float valueY)
	{
		x = valueX;
		y = valueY;
	}

	void Vector2::Move(float valueX,float valueY)
	{
		x += valueX;
		y += valueY;
	}

	Vector2& Vector2::operator*=(float val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	Vector2& Vector2::operator/=(float val)
	{
		x /= val;
		y /= val;
		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& v)
	{
		x += v.GetX();
		y += v.GetY();
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& v)
	{
		x -= v.GetX();
		y -= v.GetY();
		return *this;
	}

	Vector2 Vector2::operator+(const Vector2& v)
	{
		float newX = x + v.GetX();
		float newY = y + v.GetY();
		return Vector2(newX,newY);
	}

	Vector2 Vector2::operator-(const Vector2& v)
	{
		float newX = x - v.GetX();
		float newY = y - v.GetY();
		return Vector2(newX,newY);
	}

	Vector2 Vector2::operator/(float value)
	{
		float newX = x / value;
		float newY = y / value;
		return Vector2(newX,newY);
	}

	Vector2 Vector2::operator*(float value)
	{
		float newX = x * value;
		float newY = y * value;
		return Vector2(newX,newY);
	}

	bool Vector2::operator==(const Vector2& v)
	{
		if(x != v.GetX()) return false;
		if(y != v.GetY()) return false;
	
		return true;
	}

	bool Vector2::operator!=(const Vector2& v)
	{
		if(x != v.GetX()) return true;
		if(y != v.GetY()) return true;

		return false;
	}

	Vector2& Vector2::operator=(const Vector2& v)
	{
		x = v.GetX();
		y = v.GetY();
		return *this;
	}

	float Vector2::Distance2D(const Vector2& v)const
	{
		float xDist = abs(v.GetX() - x);
		float yDist = abs(v.GetY() - y);
		return sqrt(xDist*xDist + yDist*yDist);
	}

	float Vector2::Length()const
	{
		return sqrt(x*x + y*y);
	}

	float Vector2::DotProduct(const Vector2& v)const 
	{
		float xVal = x * v.GetX();
		float yVal = y * v.GetY();
		return xVal + yVal;
	}


	Vector2 Vector2::Normalise()const
	{
		float len = Length();
		float xVal = x/len;
		float yVal = y/len;
		return Vector2(xVal,yVal);
	}
};