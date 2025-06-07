#include "Subject.h"
#include "GameObject.h"
using namespace dae;


void Subject::AddObserver(Observer* pObserver)
{
	m_Observers.emplace_back(pObserver);
}

bool Subject::RemoveObserver(Observer* pObserver)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), pObserver);
	if (it == m_Observers.end())
		return false;

	m_Observers.erase(it);
	return true;
}

void Subject::Notify(const GameObject& game_object, const Event& event)
{
	for (Observer* pObserver : m_Observers)
	{
		pObserver->Notify(game_object, event);
	}
}