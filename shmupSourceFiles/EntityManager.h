//EntityManager.h - this is the interface for the new entity manager class - this is a custom container class that can be 
//used to keep tabs on enemies, bullets, whatever. All entities are handled in this class, and all of them are updated from this class too
//the internals use a statically sized array of entities and a statically sized array of 'indexes' to make it like a linked list
//LAST UPDATE - 23/08/11

#pragma once

#include "Behaviour.h"
#include "Movable.h"
#include "Rect.h"
#include "Sprite.h"
#include "CollisionManager.h"

namespace Advanced2D
{

	//The entity struct - contains its own sprite for appearance, position data. Also a 'movable' class for velocity and
	//direction, a member to show if it is 'active' or not, the 'type' of entity it is determined by the client
	//application and also a Rect to represent a bounding box for collision

	struct Entity
	{
		public:
			Movable				movement;
			Sprite				sprite;
			bool				active;
			Behaviour*			behaviour;
			unsigned int		id;
			Rect				AABB;
			unsigned int		type;

			Entity() {}; 

			//update calls the function that is passed in/or set as a behaviour 
			void Update(float dt) 
			{
				if(!behaviour->Update(this,dt)) 
				{
					active = false;
				}
			}

			//sets the behaviour to be called in the update;
			void SetBehaviour(Behaviour* behaviour) {this->behaviour = behaviour;}
	};


	//The actual class itself

	class EntityManager
	{
		public:
			//constructor/destructor
			EntityManager(int maxEntities);
			virtual ~EntityManager();

			//Creates an entity, returns the id given to the calling code
			unsigned int CreateEntity(Entity& description,bool hasBox = true);

			//updates all the arrays and entities contained within
			void Update(float dt);

			//Gets the entity referenced by the object id
			Entity& GetEntity(unsigned int id);

			//Draws all entities in the entitymanager
			void Draw(bool drawRects);
			
			//Sets the collision handler to manage all the AABBS of contained entities
			void SetCollisionHandler(CollisionManager* handler) {collisionHandler = handler;}

		private:
			Entity* entities;						//array of entities
			CollisionManager* collisionHandler;		//the collision handler for aabbs
			unsigned int* idToIndexTable;			//used to make it a linked list
			unsigned int activeEntityCount;			//amount of current active entities
			unsigned int nextFreeIdSlot;			//next free id slot to be used
			unsigned int MAX_ENTITIES;				// max number of entities
			Sprite* box;							//a box sprite for debug collision info
	};
}

