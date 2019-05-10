#include "MiniginPCH.h"
#include "MenuComponent.h"

void dae::MenuComponent::AddMenuOption(Vec2 pos, Levels level, int levelid)
{
	m_MenuOptions.push_back(std::tuple<Vec2, Levels, int>(pos, level, levelid));
}

void dae::MenuComponent::Update(float )
{
}
