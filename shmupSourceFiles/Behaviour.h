//Behaviour.h - this behaviour class is used to dictate different behaviours for different objects of the same type.
#pragma once

namespace Advanced2D
{
	struct Entity;

	class Behaviour
	{
		public:
			Behaviour() {};
			virtual ~Behaviour() {};
			virtual bool Update(Entity* ent,float dt) = 0;
	};
};
