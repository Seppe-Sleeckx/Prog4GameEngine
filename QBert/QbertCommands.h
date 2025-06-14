#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StateHelpers.h"
#include <string>

namespace qbert
{
	class MoveQbertCommand final : public dae::Command
	{
	public:
		MoveQbertCommand(std::weak_ptr<dae::GameObject> player, FacingDirection move_direction) : m_pQbert{ player }, m_movingDirection{ move_direction } {}
		virtual void Execute() override;

	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		FacingDirection m_movingDirection;
	};

	class QbertTakeDamageCommand final : public dae::Command
	{
	public:
		QbertTakeDamageCommand(std::weak_ptr<dae::GameObject> player, const int amount = 1.f) : m_pQbert{ player }, m_amountOfDamage{ amount } {}
		virtual void Execute() override;

	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		const int m_amountOfDamage;
	};

	class QbertRespawnCommand final : public dae::Command
	{
	public:
		QbertRespawnCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
	};

	// -----
	// Controls
	// -----
	class QbertLoseControlCommand final : public dae::Command
	{
	public:
		QbertLoseControlCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
	};

	class QbertRegainControlCommand final : public dae::Command
	{
	public:
		QbertRegainControlCommand(std::weak_ptr<dae::GameObject> pQbert, bool using_keyboard = true) : m_pQbert{ pQbert }, m_usingKeyboard{using_keyboard} {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		bool m_usingKeyboard;
	};

	class QbertBindKeyboardCommand final : public dae::Command
	{
	public:
		QbertBindKeyboardCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;

	};

	class QbertUnBindKeyboardCommand final : public dae::Command
	{
	public:
		QbertUnBindKeyboardCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
	};

	class QbertBindControllerCommand final : public dae::Command
	{
	public:
		QbertBindControllerCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
	};

	class QbertUnBindControllerCommand final : public dae::Command
	{
	public:
		QbertUnBindControllerCommand(std::weak_ptr<dae::GameObject> pQbert) : m_pQbert{ pQbert } {}
		virtual void Execute() override;
	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
	};


	// -----
	// Cubes
	// -----
	class ChangeCubeColorCommand final : public dae::Command
	{
	public:
		ChangeCubeColorCommand(std::weak_ptr<dae::GameObject> player, dae::GameObject* const pCube) : m_pQbert{ player }, m_pCube{ pCube } {}
		virtual void Execute() override;

	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		dae::GameObject* const m_pCube;
	};

	// -----
	// In game commands
	// -----
	class SkipRoundCommand final : public dae::Command
	{
	public:
		SkipRoundCommand() = default;
		virtual void Execute() override;
	};

	class MuteAudioCommand final : dae::Command
	{
	public:
		MuteAudioCommand() = default;
		virtual void Execute() override;
	};

	class LoadSinglePlayerSceneCommand final : public dae::Command
	{
	public:
		LoadSinglePlayerSceneCommand() = default;
		virtual void Execute() override;
	};

	class LoadLoadingLevelScene final : public dae::Command
	{
	public:
		LoadLoadingLevelScene(int level) : m_level{ level } {};
		virtual void Execute() override;

	private:
		const int m_level;
	};

	// -----
	// Sound
	// -----
	class PlaySoundCommand final : public dae::Command
	{
	public:
		PlaySoundCommand(const std::string sound_file, float volume = 1.f) : m_soundFile{ sound_file }, m_volume{ volume } {};
		virtual void Execute() override;

	private:
		const std::string m_soundFile;
		const float m_volume;
	};
}