#include "MiniginPCH.h"
#include "MenuIndicatorComponent.h"

void dae::MenuIndicatorComponent::AddMenuOption(std::tuple<Vec2, GameModes, Levels> Option)
{
	m_MenuOptions.push_back(Option);

}

void dae::MenuIndicatorComponent::Update(float )
{
}
