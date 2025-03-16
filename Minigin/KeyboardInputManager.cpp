#include "KeyboardInputManager.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
using namespace dae;

bool KeyboardInputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	const Uint8* key_state = SDL_GetKeyboardState(NULL);
	for (auto& key_action : m_KeyboardCommandBindings) {
		SDL_Keycode key_code = key_action.first;
		if (key_state[SDL_GetScancodeFromKey(key_code)]) {
			key_action.second->Execute();	
		}
	}

	return true;
}

void KeyboardInputManager::BindCommand(SDL_Keycode binding, std::shared_ptr<Command> pCommand)
{
	m_KeyboardCommandBindings.insert({ binding, pCommand });
}