#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "Command.h"
#include <memory>

namespace dae
{
	class KeyboardInputManager : public Singleton<KeyboardInputManager>
	{
	public:
		bool ProcessInput();
		void BindCommand(SDL_Keycode binding, std::shared_ptr<Command> pCommand);
	private:
		std::unordered_map<SDL_Keycode, std::shared_ptr<Command>> m_KeyboardCommandBindings;
	};
}


