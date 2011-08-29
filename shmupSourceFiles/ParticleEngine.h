//ParticleEngine.h - this is the basic particle engine for the shmup engine for effects such as background effects, special effects,
//explosion effect etc. This is changed from the base type - it has a bool value to indicate whether or not its particles should be
//added to the entity list as they are projectiles/bullets. This also creates an AABB to add to the collison detection system


#pragma once
#include "Includes.h"
#include "Sprite.h"
#include "Vector2.h"
#include "AABB.h"

namespace Advanced2D
{
	class ParticleEngine 
	{
		public:
			ParticleEngine();
			virtual ~ParticleEngine();

			void SetPosition(const Vector2& pos) {position = pos;}
			void SetPosition(float x,float y){position.SetX(x);position.SetY(y);}

			void SetDirection(float dir){direction = dir;}
			void SetVelocity(float vel){velocity = vel;}

			void SetMax(int num){max = num;}

			void SetAlphaRange(int min,int max){alphaMin = min;alphaMax = max;}
			
			void SetScale(float scl){scale = scl;}
			void SetLifeTime(int lifeTime) {this->lifetime = lifeTime;}
			void SetFrequency(int freq) {frequency = freq;}

			float GetDirection()const {return direction;}

			void SetImage(Texture* img);

			void Draw();
			void Update();
			void Add();

		private:
			//statically sized array of sprites
			Sprite* particles;

			Texture* image;
			bool imageLoaded;

			Vector2 position;
			float direction;
			float velocity;
			float scale;

			int maxParticles,currentNumParticles;

			int alphaMin,alphaMax;
			
			int lifetime;
			int frequency;

	};
};