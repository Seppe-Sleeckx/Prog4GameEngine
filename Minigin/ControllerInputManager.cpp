#include "ControllerInputManager.h"
using namespace dae;
bool ControllerInputManager::ProcessInput()
{
    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            //Check for all controller buttons if one is pressed
            for (auto& button_action : m_ControllerButtonCommandBindings)
            {
                if (state.Gamepad.wButtons & button_action.first) {
                    button_action.second->Execute();
                }
            }
            //Joysticks and triggers are not checked
        }
        else
        {
            // Controller is not connected
        }
    }
    return true;
}

void ControllerInputManager::BindCommand(WORD binding,std::shared_ptr<Command> pCommand)
{
	m_ControllerButtonCommandBindings.insert({ binding, pCommand });
}