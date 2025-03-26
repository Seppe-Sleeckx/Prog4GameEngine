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
		auto& command = m_KeyboardCommandBindings[e.key.keysym.sym].second;
		if (e.type == static_cast<Uint32>(m_KeyboardCommandBindings[e.key.keysym.sym].first))
		{
			command->Execute();
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void KeyboardInputManager::BindCommand(SDL_Keycode binding, std::shared_ptr<Command> pCommand, bool on_keydown)
{
	SDL_EventType type = (on_keydown ? SDL_EventType::SDL_KEYDOWN : SDL_EventType::SDL_KEYUP);
	m_KeyboardCommandBindings.insert({ binding, std::make_pair(type, pCommand)});
}

void KeyboardInputManager::UnBindCommand(SDL_KeyCode binding)
{
	m_KeyboardCommandBindings.erase(binding);
}