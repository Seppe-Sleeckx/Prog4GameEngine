#include "ControllerInputManager.h"
using namespace dae;

class ControllerInputManager::impl
{
public:
    impl() = default;
    ~impl() = default;

    bool ProcessInput()
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

    void BindCommand(WORD binding, std::shared_ptr<Command> pCommand)
    {
        m_ControllerButtonCommandBindings.insert({ binding, pCommand });
    }

    void UnBindCommand(WORD binding)
    {
        m_ControllerButtonCommandBindings.erase(binding);
    }

    void UnBindAllCommands()
    {
        m_ControllerButtonCommandBindings.clear();
    }

private:
    std::unordered_map<WORD, std::shared_ptr<Command>> m_ControllerButtonCommandBindings;
};




ControllerInputManager::ControllerInputManager() :
    pimpl{ std::make_unique<impl>() }
{

}

ControllerInputManager::~ControllerInputManager() = default;


bool ControllerInputManager::ProcessInput()
{
    return pimpl->ProcessInput();
}

void ControllerInputManager::BindCommand(WORD binding,std::shared_ptr<Command> pCommand)
{
    pimpl->BindCommand(binding, pCommand);
}

void ControllerInputManager::UnBindCommand(WORD binding)
{
    pimpl->UnBindCommand(binding);
}

void ControllerInputManager::UnBindAllCommands()
{
    pimpl->UnBindAllCommands();
}
