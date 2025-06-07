#pragma once
#include "SoundSystem.h"
#include <memory>
#include <iostream>
namespace dae
{
	class Logging_SoundSystem final : public ISoundSystem
	{
	public:
		Logging_SoundSystem(std::unique_ptr<ISoundSystem>&& real_soundSystem) : m_realSoundSystem(std::move(real_soundSystem)) {};
		virtual ~Logging_SoundSystem() = default;

		virtual void Play(sound_id sound_id, const float volume) override
		{
			m_realSoundSystem->Play(sound_id, volume);
			std::cout << "playing: " << sound_id << " at volume: " << volume << std::endl;
		}

		virtual void StopSound(sound_id sound_id) override
		{
			m_realSoundSystem->StopSound(sound_id);
		}

		virtual void StopAllSounds() override
		{
			m_realSoundSystem->StopAllSounds();
		}

		virtual sound_id LoadSound(const std::string& fileName) override
		{
			return m_realSoundSystem->LoadSound(fileName);
		}

	private:
		std::unique_ptr<ISoundSystem> m_realSoundSystem;
	};
}


