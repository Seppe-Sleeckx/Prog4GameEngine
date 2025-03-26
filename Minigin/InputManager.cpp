#include <SDL.h>
#include "InputManager.h"
#include "KeyboardInputManager.h"
#include "ControllerInputManager.h"

using namespace dae;

bool InputManager::ProcessInput()
{
	bool key_retval = KeyboardInputManager::GetInstance().ProcessInput();
	bool controller_retval = ControllerInputManager::GetInstance().ProcessInput();
	return key_retval && controller_retval;
}

void InputManager::BindCommand(SDL_Keycode binding, std::shared_ptr<Command> pCommand)
{
	KeyboardInputManager::GetInstance().BindCommand(binding, pCommand);
}

void InputManager::BindCommand(WORD binding, std::shared_ptr<Command> pCommand)
{
	ControllerInputManager::GetInstance().BindCommand(binding, pCommand);
}

void InputManager::UnBindCommand(SDL_KeyCode binding)
{
	KeyboardInputManager::GetInstance().UnBindCommand(binding);
}

void InputManager::UnBindCommand(WORD binding)
{
	ControllerInputManager::GetInstance().UnBindCommand(binding);
}