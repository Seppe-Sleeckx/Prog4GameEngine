#pragma once
namespace dae
{
	struct Event;
	class GameObject;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(const GameObject& game_object, const Event& event) = 0;
	};
}


