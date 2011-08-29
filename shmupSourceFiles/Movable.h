//Movable.h - a movable class for use in a component based oop system
#pragma once
#include "Vector2.h"


namespace Advanced2D
{
	struct Movable
	{
			Vector2 direction;
			Vector2 velocity;
	};
};