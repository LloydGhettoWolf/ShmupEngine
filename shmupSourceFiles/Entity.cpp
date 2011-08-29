//Entity.cpp
#include "Entity.h"

namespace Advanced2D
{
	Entity::Entity()
	{
		id = -1;
		name = "";
		visible = true;
		alive = true;
		objectType = 0;
		lifeTimeLength = 0;
		lifeTimeTimer.Reset();
	}
};