#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StateHelpers.h"

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

	class ChangeCubeColorCommand final : public dae::Command
	{
	public:
		ChangeCubeColorCommand(std::weak_ptr<dae::GameObject> player, dae::GameObject* const pCube) : m_pQbert{ player }, m_pCube{ pCube } {}
		virtual void Execute() override;

	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		dae::GameObject* const m_pCube;
	};

	class SkipRoundCommand final : public dae::Command
	{
	public:
		SkipRoundCommand() = default;
		virtual void Execute() override;
	};
}