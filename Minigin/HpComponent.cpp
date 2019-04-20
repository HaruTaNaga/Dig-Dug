#include "MiniginPCH.h"
#include "HpComponent.h"

void dae::HpComponent::NotifyOnDeath()
{
	
	if (m_Hp > 0) 
	{ 
		m_Hp--;
		m_HpUiComp.NotifyHpChanged(m_Hp);
	}
	
}
