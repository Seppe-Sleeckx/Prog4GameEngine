#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StateHelpers.h"

namespace qbert
{
	class MoveQbertCommand : public dae::Command
	{
	public:
		MoveQbertCommand(std::shared_ptr<dae::GameObject> player, FacingDirection move_direction) : m_Qbert{ player }, m_movingDirection{ move_direction } {}
		virtual void Execute() override;

	private:
		std::shared_ptr<dae::GameObject> m_Qbert;
		FacingDirection m_movingDirection;
	};
}