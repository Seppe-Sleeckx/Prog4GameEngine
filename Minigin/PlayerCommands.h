#pragma once
#include "Command.h"
#include "GameObject.h"
#include <glm.hpp>

namespace dae
{
	class MovePlayerCommand : public Command
	{
	public:
		MovePlayerCommand(std::shared_ptr<GameObject> player, glm::vec2 direction) : m_player{ player }, m_direction { direction } {}
		virtual void Execute() override;

	private:
		std::shared_ptr<GameObject> m_player;
		glm::vec2 m_direction{};
	};
}

