#include "MiniginPCH.h"
#include "HpUiComponent.h"

dae::HpUiComponent::HpUiComponent(TextComponent & texc) : m_TextComponent(texc)
{
	m_TextComponent.SetText("Hp : 3" );
}



void dae::HpUiComponent::NotifyHpChanged(int hp)
{
	m_TextComponent.SetText("Hp : " + std::to_string(hp));
}
