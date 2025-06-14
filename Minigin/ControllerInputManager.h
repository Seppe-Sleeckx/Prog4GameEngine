#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Windows.h"
#include "Xinput.h"
#include <memory>

namespace dae
{
	class ControllerInputManager : public Singleton<ControllerInputManager>
	{
	public:
		ControllerInputManager();
		~ControllerInputManager();

		bool ProcessInput();
		void BindCommand(WORD binding, std::shared_ptr<Command> pCommand);
		void UnBindCommand(WORD binding);
		void UnBindAllCommands();

	private:
		//XINPUT_Joysticks dont return a true or false value but either a value between [0-255] or [-32768 - 32767]
		class impl;
		std::unique_ptr<impl> pimpl;
	};
}
