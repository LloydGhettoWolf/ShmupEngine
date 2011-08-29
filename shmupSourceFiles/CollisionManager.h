//CollisionManager - 
//LAST UPDATE 27/08/11

#pragma once
#include "Rect.h"

namespace Advanced2D
{
	const int MAX_BOXES = 10000;
	const int MAX_ENCOUNTERS = 500;
	const int COLLISION_MAP_SIZE = 5;
	const int X_AXIS = 0;
	const int Y_AXIS = 1;
	const int MIN    = 0;
	const int MAX    = 1;
	const int SHUFFLE_OUT = 2000;

	//two structs used for collison handling
	//An encounter to hold the ids of the two entities colliding
	struct CollisionEncounter
	{
		int objIds[2];
	};

	//end points for the min and max of the aabb to be tested
	struct EndPoint
	{
		unsigned int type;
		unsigned int objID;
		unsigned int objType;
		float value;
	};

	class CollisionManager
	{
		public:
			CollisionManager();
			virtual ~CollisionManager(){};

			void InitMap(unsigned int map[][COLLISION_MAP_SIZE],unsigned int size);

			void Update();

			void ResolveEncounters();
			void AddEncounter(int objID1,int objID2);
			void RemoveEncounter(int objID1);

			int  AddBox(int objID,float left,float right, float top,float bottom,int type);
			void RemovePoints(int boxID);
			void UpdateBox(unsigned int objId,float left,float top,float right,float bottom);

			bool Collide(unsigned int objId1,unsigned int objId2);
			inline bool CheckMap(int type1,int type2);
			void FindEndPoints(unsigned int objId,float& xMin,float& xMax,float& yMin,float& yMax);

		private:
			//array of 'encounters' to be held  
			CollisionEncounter encounters[MAX_ENCOUNTERS];

			//Array of endpoints 
			EndPoint endpoints[2*MAX_BOXES][2]; 

			//variables to keep track of encounters and boxes
			unsigned int numEncounters;
			unsigned int numBoxes;

			unsigned int collisionMap[COLLISION_MAP_SIZE][COLLISION_MAP_SIZE];
	};
};