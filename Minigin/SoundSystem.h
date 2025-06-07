#pragma once
#include <string>
using sound_id = short;
class ISoundSystem
{
public:
	virtual ~ISoundSystem() {};
	virtual void Play(sound_id sound_id, const float volume) = 0;
	virtual void StopSound(sound_id sound_id) = 0;
	virtual void StopAllSounds() = 0;
	virtual sound_id LoadSound(const std::string& fileName) = 0;
};

