//CollisionManager.cpp
#include "CollisionManager.h"
#include "Advanced2D.h"

namespace Advanced2D
{

	CollisionManager::CollisionManager()
	{
		numBoxes = 0;
		numEncounters = 0;
	}

	void CollisionManager::InitMap(unsigned int map[][COLLISION_MAP_SIZE],unsigned int mapSize)
	{

		for(int y = 0; y < COLLISION_MAP_SIZE; y++)
		{
			for(int x = 0; x < COLLISION_MAP_SIZE; x++)
			{
				collisionMap[x][y] = map[x][y];
			}
		}
	}

	void CollisionManager::Update()
	{
		//sort through lists on the x and y axis to employ the sweep and prune strategy

		for(int axis = X_AXIS; axis <= Y_AXIS; axis++)
		{
			//go through each box, and go through both the max and min
			//endpoints for each box in the current axis so this will need
			//twice the amount of normal tests
			for(int box = 1; box < numBoxes * 2; box++)
			{
				int keyType = endpoints[box][axis].type;
				int keyVal = endpoints[box][axis].value;
				int keyBoxId = endpoints[box][axis].objID;

				//use the above keyval to the value before it in the array - swap if necessary
				//it's basically a bubblesort
				int index = box-1;
				
				//now go backwards to the start of the array to make sure it is all in the right order
				while(index >= 0)
				{
					int compType = endpoints[index][axis].type;
					int compBoxId = endpoints[index][axis].objID;

					int compVal =  endpoints[index][axis].value;
					int objType1 = endpoints[box][axis].objType;
					int objType2 = endpoints[index][axis].objType;

					if(compVal < keyVal)
					{
						//this is in order so break the loop
						break;
					}

					
					if((compType == 1) && (keyType == 0))
					{
						//is this an encounter we're interested in?
						if(CheckMap(objType1,objType2))
						{
							
							if(Collide(endpoints[index][axis].objID,endpoints[index+1][axis].objID))
							{
								AddEncounter(endpoints[index][axis].objID,endpoints[index+1][axis].objID);
							}
							
						}
					
					}

					//swap the points
					EndPoint temp = endpoints[index][axis];
					endpoints[index][axis]   = endpoints[index+1][axis];
					endpoints[index+1][axis] = temp;
					
					index--;
				}//end while

			}//end inner for loop

		}

		ResolveEncounters();
	}

	void CollisionManager::ResolveEncounters()
	{
		//will have to be done later - pass the owner entities of these rects to the 
		//collision resolution code in the actual game - call this code by going 
		//through the list of encounters one by one 
		for(int encounter = 0; encounter < numEncounters; encounter++)
		{
			int id1 = encounters[encounter].objIds[0];
			int id2 = encounters[encounter].objIds[1];
			g_engine->DealWithCollision(id1,id2);
			RemoveEncounter(id1);
		}
	}

	void CollisionManager::AddEncounter(int objID1,int objID2)
	{
		
		for(int encounter = 0; encounter < numEncounters; encounter++)
		{
			//add a new encounter to a list 
			//make sure it doesn't sit in the list already
			if((encounters[encounter].objIds[0]  == objID1 && encounters[encounter].objIds[1] == objID2) ||
				(encounters[encounter].objIds[0] == objID2 && encounters[encounter].objIds[1] == objID1))
			{
				//if it does exist return from the function
				return;
			}
		}

		//otherwise it obviously doesn't sit in the encounters list yet, so add it!

		encounters[numEncounters].objIds[0] = objID1;
		encounters[numEncounters].objIds[1] = objID2;
		numEncounters++;
	}

	void CollisionManager::RemoveEncounter(int objID1)
	{
		//remove the encounter
		//search through and look for it
		for(int encounter = 0; encounter < numEncounters; encounter++)
		{
			//if encounter found, remove it
			if((encounters[encounter].objIds[0] == objID1 || encounters[encounter].objIds[1] == objID1))
			{
				for(int index = encounter; index < numEncounters-1; index++)
				{
					encounters[index] = encounters[index+1];
				}
				numEncounters--;
				return;
			}
		}
	}

	int CollisionManager::AddBox(int objID,float left,float top,float right,float bottom,int objType)
	{
		//will need to add some code re obj id
		//may have to get entities involved
		//add AABB

		//add endpoints
		endpoints[2 * numBoxes][X_AXIS].type			= MIN;
		endpoints[2 * numBoxes][X_AXIS].objID			= objID;
		endpoints[2 * numBoxes][X_AXIS].objType			= objType;
		endpoints[2 * numBoxes][X_AXIS].value			= left;

		endpoints[2 * numBoxes + 1][X_AXIS].type		= MAX;
		endpoints[2 * numBoxes + 1][X_AXIS].objID		= objID;
		endpoints[2 * numBoxes + 1][X_AXIS].objType		= objType;
		endpoints[2 * numBoxes + 1][X_AXIS].value		= right;

		endpoints[2 * numBoxes][Y_AXIS].type			= MIN;
		endpoints[2 * numBoxes][Y_AXIS].objID			= objID;
		endpoints[2 * numBoxes][Y_AXIS].objType			= objType;
		endpoints[2 * numBoxes][Y_AXIS].value			= top;

		endpoints[2 * numBoxes + 1][Y_AXIS].type		= MAX;
		endpoints[2 * numBoxes + 1][Y_AXIS].objID		= objID;
		endpoints[2 * numBoxes + 1][Y_AXIS].objType		= objType;
		endpoints[2 * numBoxes + 1][Y_AXIS].value		= bottom;

		numBoxes++;
		return numBoxes-1;
	}

	void CollisionManager::RemovePoints(int objID)
	{
		//this removes the box with the passed in id from the list - from the encounters list,
		//the endpoints list 

		//endpoints - there will be two x points and two y points - they
		//may not be next to each other in the array so we will need to check for both and
		//shuffle accordingly - we can give them a high const value and they will be 'shuffled' out
		//on the next pass

		for(int box = 0; box < numBoxes * 2; box++)
		{
			if(endpoints[box][X_AXIS].objID == objID)
			{
				endpoints[box][X_AXIS].value = SHUFFLE_OUT;
			}

			if(endpoints[box][Y_AXIS].objID == objID)
			{
				endpoints[box][Y_AXIS].value = SHUFFLE_OUT;
			}
			
		}

		Update();
		RemoveEncounter(objID);

		numBoxes--;
	}


	void CollisionManager::UpdateBox(unsigned int objId,float left,float right,float top,float bottom)
	{
		//x axis
		for(int box = 0; box < numBoxes*2; box++)
		{
			if(endpoints[box][X_AXIS].objID == objId && endpoints[box][0].type == MIN)
			{
				//update the box
				endpoints[box][X_AXIS].value = left;
			}

			if(endpoints[box][X_AXIS].objID == objId && endpoints[box][0].type == MAX)
			{
				//update the box
				endpoints[box][X_AXIS].value = right;
				break;
			}
		}

		//y axis
		for(int box = 0; box < numBoxes*2; box++)
		{
			if(endpoints[box][Y_AXIS].objID == objId && endpoints[box][1].type == MIN)
			{
				//update the box
				endpoints[box][Y_AXIS].value = top;
			}

			if(endpoints[box][Y_AXIS].objID == objId && endpoints[box][1].type == MAX)
			{
				//update the box
				endpoints[box][Y_AXIS].value = bottom;
				break;
			}
		}
	}

	bool CollisionManager::Collide(unsigned int objId1,unsigned int objId2)
	{
		//get the x and y vals of objId1 and objId2
		float xMin1,xMax1,xMin2,xMax2;
		float yMin1,yMax1,yMin2,yMax2;
		FindEndPoints(objId1,xMin1,xMax1,yMin1,yMax1);
		FindEndPoints(objId2,xMin2,xMax2,yMin2,yMax2);

		//Create boxes
		Rect rect1(xMin1,yMin1,xMax1-xMin1,yMax1-yMin1);
		Rect rect2(xMin2,yMin2,xMax2-xMin2,yMax2-yMin2);

		//test and return if false

		return rect1.TestIntersect(rect2);
	}

	bool CollisionManager::CheckMap(int type1,int type2)
	{
		return (collisionMap[type1][type2] == 1);
	}

	void CollisionManager::FindEndPoints(unsigned int objId,float& xMin,float& xMax,float& yMin,float& yMax)
	{
		//x axis
		for(int box = 0; box < numBoxes*2; box++)
		{
			if(endpoints[box][X_AXIS].objID == objId && endpoints[box][0].type == MIN)
			{
				//update the box
				xMin = endpoints[box][X_AXIS].value;
			}

			if(endpoints[box][X_AXIS].objID == objId && endpoints[box][0].type == MAX)
			{
				//update the box
				xMax = endpoints[box][X_AXIS].value;
				break;
			}
		}

		//y axis
		for(int box = 0; box < numBoxes*2; box++)
		{
			if(endpoints[box][Y_AXIS].objID == objId && endpoints[box][1].type == MIN)
			{
				//update the box
				yMin = endpoints[box][Y_AXIS].value;
			}

			if(endpoints[box][Y_AXIS].objID == objId && endpoints[box][1].type == MAX)
			{
				//update the box
				yMax = endpoints[box][Y_AXIS].value;
				break;
			}
		}
	}
};