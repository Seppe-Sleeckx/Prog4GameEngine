#pragma once
#include "Singleton.h"
#include "Command.h"
#include <Windows.h>
#include "Xinput.h"
#include <memory>
#include <SDL.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void BindCommand(SDL_Keycode binding, std::shared_ptr<Command> pCommand);
		void BindCommand(WORD binding, std::shared_ptr<Command> pCommand);
		void UnBindCommand(SDL_KeyCode binding);
		void UnBindCommand(WORD binding);
		void UnBindAllCommands();
	};

}
