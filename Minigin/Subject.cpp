#include "Subject.h"
#include "GameObject.h"
using namespace dae;


void Subject::AddObserver(IObserver* pObserver)
{
	m_Observers.emplace_back(pObserver);
}

bool Subject::RemoveObserver(IObserver* pObserver)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), pObserver);
	if (it == m_Observers.end())
		return false;

	m_Observers.erase(it);
	return true;
}

void Subject::Notify(const GameObject& game_object, const Event& event)
{
	for (IObserver* pObserver : m_Observers)
	{
		pObserver->Notify(game_object, event);
	}
}