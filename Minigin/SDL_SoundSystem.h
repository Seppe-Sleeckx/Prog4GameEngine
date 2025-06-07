#pragma once
#include "SoundSystem.h"
#include <SDL_mixer.h>//fix should be sdl_mixer.h but not accessible
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace dae
{
	class SDL_SoundSystem final : public ISoundSystem
	{
	public:
		SDL_SoundSystem() { 
			InitMixer();
			m_workerThread = std::jthread([this](std::stop_token st) {WorkerLoop(st);});
		}
		virtual ~SDL_SoundSystem() {
			m_waitCondition.notify_one();
			QuitMixer();
		};
		//Rule of five
		SDL_SoundSystem(const SDL_SoundSystem&) = delete;
		SDL_SoundSystem(SDL_SoundSystem&& other) = delete;
		SDL_SoundSystem& operator=(const SDL_SoundSystem& other) = delete;
		SDL_SoundSystem& operator=(SDL_SoundSystem&& other) = delete;

		void InitMixer();
		void QuitMixer();

		virtual void Play(sound_id audio_id, const float volume) override;
		virtual void StopSound(sound_id audio_id) override;
		virtual void StopAllSounds() override;
		virtual sound_id LoadSound(const std::string& fileName) override;

	private:
		std::vector<Mix_Chunk*> m_AudioClips;

		void WorkerLoop(std::stop_token stop_token);
		//Threading
		std::queue<std::pair<Mix_Chunk*, float>> m_SoundQueue;
		std::mutex m_QueueMutex;
		std::mutex m_AudioClipsMutex;
		std::condition_variable_any m_waitCondition;
		std::jthread m_workerThread;
	};
}

