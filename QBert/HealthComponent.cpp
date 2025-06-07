#include "HealthComponent.h"
#include "Event.h"

using namespace dae;


void HealthComponent::TakeDamage(float damage_amount)
{
	m_Health -= damage_amount;
	if(m_Health <= 0.f)
		m_Subject->Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerDied") });
}