#include "MiniginPCH.h"
#include "DeathComponent.h"
#include  "ComponentsH.h"
void dae::DeathComponent::NotifyOnDeath()
{
	
		m_HasDied = true;
		m_HpComponent.NotifyOnDeath();
	
}
