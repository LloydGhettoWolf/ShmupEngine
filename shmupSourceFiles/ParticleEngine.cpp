//ParticleEngine.cpp

#include "ParticleEngine.h"

namespace Advanced2D
{
	ParticleEngine::ParticleEngine( )
	{
		image = NULL;
		maxParticles = 100;
		direction  = 0;
		alphaMin = 254;
		alphaMax = 255;
		velocity = 1.0f;
		scale = 1.0f;
		frequency = 100;
		
	}

	ParticleEngine::~ParticleEngine()
	{
		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			delete *particle;
		}
		particles.clear();
	}


	void ParticleEngine::SetImage(Texture* img)
	{
		image = img;
		imageLoaded = false;
	}

	void ParticleEngine::Add()
	{
		static float PI_DIV_180 = 3.14159/180.0f;
		float vX,vY;
		Sprite* p = new Sprite();
		p->SetImage(image);
		p->SetPosition(position.GetX(),position.GetY());

		double dir = direction - 90.0f;
		vX = cos(dir * PI_DIV_180);
		vY = sin(dir * PI_DIV_180);
		p->SetVelocity(vX * velocity,vY * velocity);

	
		p->SetScale(scale);
		particles.push_back(p);
	}

	void ParticleEngine::Draw()
	{
		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			(*particle)->Draw();
		}
	}

	void ParticleEngine::Update()
	{
		static Timer timer;

		if((int)particles.size() < max)
		{
			if(timer.StopWatch(frequency))Add();
		}

		for(iter particle = particles.begin(); particle != particles.end(); particle++)
		{
			(*particle)->Update();


			if((*particle)->GetPosition().Distance2D(position) > 750.0f)
			{
				delete *particle;
				*particle = particles.back();
				particles.erase(particles.end()-1);
			}
		}
	}



};