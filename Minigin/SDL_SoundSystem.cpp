#include "SDL_SoundSystem.h"
#include <iostream>
#include <SDL.h>
using namespace dae;

void SDL_SoundSystem::InitMixer()
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
		std::cout << "Failed to initialize SDL audio subsystem: " << SDL_GetError() << "\n";
    }
	
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        std::cout << "Failed to open audio: " << Mix_GetError() << "\n";
    }
	
    Mix_AllocateChannels(16);
}

void SDL_SoundSystem::QuitMixer()
{
	std::unique_lock audio_lock(m_AudioClipsMutex);
	for (auto clip : m_AudioClips)
	{
		Mix_FreeChunk(clip);
	}
	m_AudioClips.clear();
	audio_lock.unlock();
	
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);	
}

void SDL_SoundSystem::Play(sound_id audio_id, const float volume)
{
	std::scoped_lock Queue_lock(m_QueueMutex);

	std::unique_lock sound_clips_lock(m_AudioClipsMutex);
	auto audio_clip = m_AudioClips[audio_id];
	sound_clips_lock.unlock();

	if (audio_clip != nullptr)
	{
		m_SoundQueue.emplace(audio_clip, volume);
		m_waitCondition.notify_one();
	}
}

void SDL_SoundSystem::WorkerLoop(std::stop_token stop_token)
{
	while (!stop_token.stop_requested())
	{
		std::unique_lock queue_lock(m_QueueMutex);
		m_waitCondition.wait(queue_lock, stop_token, [this] {
			return !m_SoundQueue.empty();
			});
		
		while (!m_SoundQueue.empty())
		{
			auto [sound_clip, volume] = m_SoundQueue.front();
			m_SoundQueue.pop();
			queue_lock.unlock();
			//unlock, Begin processing allowing new items to be added whilst processing
			if (sound_clip != nullptr)
			{
				Mix_VolumeChunk(sound_clip, static_cast<int>(volume * MIX_MAX_VOLUME));
				Mix_PlayChannel(-1, sound_clip, 0);
			}
			//End processing and lock again, to prevent new items being added whilst checking others
			queue_lock.lock();
		}
	}
}

void SDL_SoundSystem::StopSound(sound_id audio_id)
{
	std::unique_lock audio_clips_lock(m_AudioClipsMutex);
	if (audio_id < 0 || audio_id > std::ssize(m_AudioClips))
	{
		std::cout << "Invalid audio_id: " << audio_id << "\n";
	}

	auto audio_clip = m_AudioClips[audio_id];
	audio_clips_lock.unlock();

	if (audio_clip != nullptr)
	{
		int numChannels = Mix_AllocateChannels(-1);
		for (int i = 0; i < numChannels; ++i)
		{
			if (Mix_GetChunk(i) == audio_clip)
			{
				Mix_HaltChannel(i);
				break;
			}
		}
	}
}

void SDL_SoundSystem::StopAllSounds()
{
	Mix_HaltChannel(-1);
}

sound_id SDL_SoundSystem::LoadSound(const std::string& fileName)
{
	Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());
	if (sound == nullptr)
	{
		std::cout << "Failed to load music. SDL_Mixer error: \n" << Mix_GetError() << std::endl;
		return -1;
	}
	std::scoped_lock audio_clips_lock(m_AudioClipsMutex);
	m_AudioClips.emplace_back(sound);
	return static_cast<sound_id>(std::ssize(m_AudioClips) - 1);
}