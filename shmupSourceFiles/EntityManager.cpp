//EntityManager.cpp - 
//LAST UPDATE 23/08/11

#include "EntityManager.h"
#include "Advanced2D.h"

namespace Advanced2D
{

	//Constructor - takes a max number of entities to be handled
	EntityManager::EntityManager(int maxEntities) : 
								entities(NULL),idToIndexTable(NULL),nextFreeIdSlot(0),activeEntityCount(0),MAX_ENTITIES(maxEntities)
	{
		//create the array of entities and id table
		entities = new Entity[MAX_ENTITIES];
		idToIndexTable = new unsigned int[MAX_ENTITIES];


		//initialise the indexes in the table
		for(unsigned int t = 0; t <  MAX_ENTITIES; ++t)
			idToIndexTable[t] = t + 1;

		//create the box sprite, assign the texture
		box = new Sprite;
		box->LoadImg("hilight.tga");
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Destructor
	EntityManager::~EntityManager()
	{
		//delete the two statically sized arrays
		delete [] entities;
		delete [] idToIndexTable;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create an entity and pass the obj id back to the calling code
	//for use for look up later. It takes in a 'description' of the entity as an argument
	//that dictates its behaviour/type etc. It also takes a bool to say if this is a collidable
	//entity or not

	unsigned int EntityManager::CreateEntity(Entity& description,bool hasBox)
	{
		  //Take a reference to the next free entity slot
		  Entity& l_new_entity = entities[activeEntityCount];

		  //assign the passed in description
		  l_new_entity = description;

		  //make sure it is active
		  l_new_entity.active = true;

		  //get an id using the next free id slot
		  unsigned int id = nextFreeIdSlot;
		  l_new_entity.id = id;

		  // we update the next free id slot for use by the next entity
		  nextFreeIdSlot = idToIndexTable[id];

		  //set the id in the index table to the next one to be used
		  idToIndexTable[id] = activeEntityCount++;

		  //if there is a need for an aabb - create it and add it to the collision manager
		  if(hasBox)
		  {
			  int left   = l_new_entity.sprite.GetX() + l_new_entity.AABB.vals[0][0];
			  int right  = left + l_new_entity.AABB.vals[1][0];
			  int top    = l_new_entity.sprite.GetY() + l_new_entity.AABB.vals[0][1];
			  int bottom = top + l_new_entity.AABB.vals[1][1];

			  //also add the box to the collisionHandler if there is a collision box
			  l_new_entity.AABB.vals[0][0] = left;
			  l_new_entity.AABB.vals[1][0] = right;
			  l_new_entity.AABB.vals[0][1] = top;
			  l_new_entity.AABB.vals[1][1] = bottom;

			  //add the box to the collision handler - assign the returned box id for later use
			  //for lookup/removal
			  l_new_entity.AABB.boxID = collisionHandler->AddBox(l_new_entity.id,left,top,right,bottom,l_new_entity.type);
		  }

		   return id;
		
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Update - this updates all of the the entities contained in the main array, updates the main array by
	//sorting out any 'inactive' entities and finally update the the associated aabbs
	void EntityManager::Update(float dt)
	{
		//index used for going through the array of entities
		 unsigned int l_new_index = 0;
		
		//go through all the currently active entities
		for(unsigned int t = 0; t < activeEntityCount; ++t) 
		{
			//get a ref to the current entity being perused
			Entity& l_entity = entities[t];

			//take the xpos
			float xPos = l_entity.sprite.GetX();
			float yPos = l_entity.sprite.GetY();

			//call the update code

			l_entity.Update(dt);

			//take new x/y pos
			float xDiff = l_entity.sprite.GetX() - xPos;
			float yDiff = l_entity.sprite.GetY() - yPos;

			//use the above to update its AABB accordingly
			l_entity.AABB.vals[0][0] += xDiff;
			l_entity.AABB.vals[1][0] += xDiff;
			l_entity.AABB.vals[0][1] += yDiff;
			l_entity.AABB.vals[1][1] += yDiff;
			

			//use the new data to update this entity's box
			collisionHandler->UpdateBox(l_entity.id,l_entity.AABB.vals[0][0],l_entity.AABB.vals[1][0],
										l_entity.AABB.vals[0][1],l_entity.AABB.vals[1][1]);
      
			//if the entity is active update it's position in the array
			if(l_entity.active) 
			{
				  if(t != l_new_index) 
				  {
						// if a bullet was destroyed before adjust the index-tables
						// and move the bullet down in the array accordingly. 

						entities[l_new_index] = l_entity;
						idToIndexTable[l_entity.id] = l_new_index;
				  }

				  ++l_new_index;
			} 
			else 
			{
			  // when a bullet is removed we have to "fix" the free-IDs-pseudo-linked-list.
			  // that's easy: we just let the bullet's slot point to the known next free ID
			  // which we stored during bullet creation...

			  idToIndexTable[l_entity.id] = nextFreeIdSlot;

			  //also remember to remove it's box from the collisionHandler
			  collisionHandler->RemovePoints(l_entity.id);

			  // ... and make that slot the new "next_free" slot (like adjusting the head of a linked list)
			  nextFreeIdSlot = l_entity.id;
			}
      }
      activeEntityCount = l_new_index;
	}

	//Get the entity using its id and the idToIndexTable lookup
	Entity& EntityManager::GetEntity(unsigned int id)
	{
		return entities[idToIndexTable[id]];
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//draw all of the entities - comes with a bool to draw collision rects for debugging purposes
	void EntityManager::Draw(bool drawRects)
	{
		//for each entity that is active
		for(unsigned int entity = 0; entity < activeEntityCount; entity++)
		{
			//if it is actually active try and draw it
			if(entities[entity].active)
				entities[entity].sprite.Draw();
			
		}

		//draw the rects if flagged
		if(drawRects)
		{
			for(unsigned int entity = 0; entity < activeEntityCount; entity++)
			{
				int left	= entities[entity].AABB.vals[0][0];
				int right	= entities[entity].AABB.vals[1][0];
				int top		= entities[entity].AABB.vals[0][1];
				int bottom	= entities[entity].AABB.vals[1][1];
				box->SetPosition(left,top);
				box->SetColour(0x33DD4444);
				box->Draw();
			}
		}
	}

};