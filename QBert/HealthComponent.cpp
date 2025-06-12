#include "HealthComponent.h"
#include "Event.h"

using namespace dae;


void HealthComponent::TakeDamage(int damage_amount)
{
	m_Health -= damage_amount;
	m_Subject->Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerTookDamage") });

	if(m_Health <= 0)
		m_Subject->Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerDied") });
}