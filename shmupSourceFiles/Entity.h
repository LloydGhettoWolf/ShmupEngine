//Entity.h - the entity class - this represents any kind of updatable 'entity' in the game - enemies, powerups, the player etc
//also now supports "particle engines" as entities.
//Last update - 19/08/2011

#pragma once
#include "Includes.h"
#include "Timer.h"

namespace Advanced2D
{

	class Entity
	{
		public:
			Entity();

			//virtual destructor to call the correct destructor
			virtual ~Entity() {};

			//pure virtual functions
			virtual void Update() = 0;
			virtual void Animate() = 0;
			virtual void Draw() = 0;
			
			//Accessors for entity info - object id etc
			int  GetID()const {return id;}
			bool GetVisible()const{ return visible;}
			bool GetAlive()const {return alive;}

			const std::string& GetName()const {return name;}

			int  GetLifeTime()const {return lifeTimeLength;}
			int  GetObjectType(){return objectType;}
			
			//mutators for entity info
			void SetID(int value) {id = value;}
			void SetName(std::string& nme){name = nme;}
			void SetVisible(bool value) {visible = value;}
			void SetAlive(bool value) {alive = value;}
			void SetLifeTime(int value){lifeTimeLength = value;lifeTimeTimer.Reset();}
			bool LifeTimeExpired() {return lifeTimeTimer.StopWatch(lifeTimeLength);}
			void SetObjectType(int value){objectType = value;}

		protected:
			int id;
			std::string name;
			bool visible;
			bool alive;
			int objectType;
			int lifeTimeLength;
			Timer lifeTimeTimer;			
	};
};