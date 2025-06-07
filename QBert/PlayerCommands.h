#pragma once
#include "Command.h"
#include "GameObject.h"
#include <string>
#include <glm.hpp>
#include "SoundSystem.h"

namespace dae
{
	class MovePlayerCommand final : public Command
	{
	public:
		MovePlayerCommand(std::shared_ptr<GameObject> player, glm::vec2 direction) : m_player{ player }, m_direction { direction } {}
		virtual void Execute() override;

	private:
		std::shared_ptr<GameObject> m_player;
		glm::vec2 m_direction{};
	};

	class TakeDamageCommand final : public Command
	{
	public:
		TakeDamageCommand(std::shared_ptr<GameObject> player) : m_player{ player } {};
		virtual void Execute() override;

	private:
		std::shared_ptr<GameObject> m_player;
		inline static const float DAMAGE_AMOUNT = 1.f;
	};

	class IncreaseScoreCommand final : public Command
	{
	public:
		IncreaseScoreCommand(std::shared_ptr<GameObject> player, const float score_amount) : m_player{ player }, m_scoreAmount{ score_amount } {};
		virtual void Execute() override;
	private:
		std::shared_ptr<GameObject> m_player;
		const float m_scoreAmount = 10.f;
	};

	class PlaySoundCommand final : public Command
	{
	public:
		PlaySoundCommand(const std::string& soundFile);
		virtual void Execute() override;
	private:
		sound_id m_soundId = -1;
	};
}

