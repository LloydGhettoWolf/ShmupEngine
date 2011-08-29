//Vector2.h - This class represents a 2D vector for use in the engine by sprites, particle emitters etc
//Last Update 15/08/2011

#pragma once
#include "Includes.h"

namespace Advanced2D
{
	class Vector2
	{
		public:
			Vector2();
			Vector2(const Vector2& v);
			Vector2(float valueX,float valueY);
			Vector2(int valueX,int valueY);
			void Set(float valueX,float valueY);
			void Set(const Vector2& v);
			void SetX(float value) {x = value;}
			void SetY(float value) {y = value;}

			float GetX()const {return x;}
			float GetY()const {return y;}

			void Move(float xValue,float yValue);

			//compound operators
			Vector2& operator+=(const Vector2& v);
			Vector2& operator-=(const Vector2& v);
			Vector2& operator*=(float val);
			Vector2& operator/=(float val);

			//arithmetic operators
			Vector2 operator+(const Vector2& v);
			Vector2 operator-(const Vector2& v);
			Vector2 operator*(float val);
			Vector2 operator/(float val);

			//boolean operators
			bool operator==(const Vector2& v);
			bool operator!=(const Vector2& v);

			//assignment
			Vector2& operator=(const Vector2& v);

			//other operators
			float Distance2D(const Vector2& v)const;
			float Length()const;
			float DotProduct(const Vector2& v)const;
			Vector2 Normalise()const;
		private:
			float x,y;
	};
};