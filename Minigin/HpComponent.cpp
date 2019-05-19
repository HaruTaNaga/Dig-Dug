#include "MiniginPCH.h"
#include "HpComponent.h"
#include "IObserver.h"
void dae::HpComponent::NotifyOnDeath()
{
	
	if (m_Hp > 1) 
	{ 
		m_Hp--;
		m_HpUiComp.NotifyHpChanged(m_Hp);
	}
	else
	{
		for (auto & observer : m_Observers)
		{
			observer->Notify(EventTypes::PlayerDied);
		}
	}
	
}
