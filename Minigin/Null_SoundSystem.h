#pragma once
#include "SoundSystem.h"
namespace dae
{
	class Null_SoundSystem final : public ISoundSystem
	{
	public:
		virtual ~Null_SoundSystem() {};
		virtual void Play(sound_id, const float) override {};
		virtual void StopSound(sound_id) override {};
		virtual void StopAllSounds() override {};
		virtual sound_id LoadSound(const std::string&) override { return -1; };
	};
}

