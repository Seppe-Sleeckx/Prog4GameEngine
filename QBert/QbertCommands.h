#pragma once
#include "Command.h"
#include "GameObject.h"
#include "StateHelpers.h"

namespace qbert
{
	class MoveQbertCommand : public dae::Command
	{
	public:
		MoveQbertCommand(std::weak_ptr<dae::GameObject> player, FacingDirection move_direction) : m_pQbert{ player }, m_movingDirection{ move_direction } {}
		virtual void Execute() override;

	private:
		std::weak_ptr<dae::GameObject> m_pQbert;
		FacingDirection m_movingDirection;
	};
}