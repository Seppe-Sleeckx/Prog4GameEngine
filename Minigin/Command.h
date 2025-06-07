#pragma once
#include <functional>

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

	private:
	};

	class EditorCommand : Command
	{
	public:
		virtual ~EditorCommand() = default;
		virtual void Undo() = 0;
	};
}

