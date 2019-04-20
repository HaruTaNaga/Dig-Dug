#include "MiniginPCH.h"
#include "HpUiComponent.h"

void dae::HpUiComponent::Update(float )
{
	m_TextComponent.SetText( "Hp : " + std::to_string(m_Hp));
}
