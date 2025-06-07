#pragma once
#include "SoundSystem.h"
#include "Null_SoundSystem.h"
#include <memory>
namespace dae
{
    class ServiceLocator final
    {
    public:
        static ISoundSystem& GetSoundSystem() { return *_audio_service; }

        static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& sound_system) { _audio_service = sound_system == nullptr ? std::make_unique<Null_SoundSystem>() : std::move(sound_system); }

    private:
        inline static std::unique_ptr<ISoundSystem> _audio_service = std::make_unique<Null_SoundSystem>();
    };
}

