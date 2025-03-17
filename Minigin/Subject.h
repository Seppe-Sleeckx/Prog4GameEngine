#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		//Rule of five
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;


		void AddObserver(Observer* pObserver);
		bool RemoveObserver(Observer* pObserver);
		void Notify(const GameObject& game_object, const Event& event);
	private:
		std::vector<Observer*> m_Observers;
	};
}


