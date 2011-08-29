//Audio.h - all interface code for audio is right here
#pragma once
#include "Includes.h"
#include <fmod.hpp>

namespace Advanced2D
{
	class Sample
	{
		public:
			FMOD_SOUND* sample;
			FMOD_CHANNEL* channel;
			Sample();
			~Sample();
			const std::string& GetName()const {return name;}
			void SetName(const std::string& fileName) {name = fileName;}
		private:
			std::string name;
	};

	class Audio
	{
		public:
			Audio();
			~Audio();
			FMOD_SYSTEM* GetSystem()const {return system;}
			bool Init();
			void Update();
			bool Load(const std::string& fileName, const std::string& name);
			Sample* Load(const std::string& fileName);
			bool Play(const std::string& name);
			bool Play(Sample* sample);
			void Stop(const std::string& name);
			void StopAll();
			void StopAllExcept(const std::string& name);
			bool IsPlaying(const std::string& name);
			bool SampleExists(const std::string& name);
			Sample* FindSample(const std::string& name);
		private:
			FMOD_SYSTEM* system;
			typedef std::vector<Sample*> Samples;
			typedef std::vector<Sample*>::iterator SampleItr;
			Samples samples;
	};
};