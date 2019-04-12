#include "MiniginPCH.h"
#include "PositionComponent.h"





const glm::vec3 & dae::PositionComponent::GetPosition()
{
	return m_Transform.GetPosition();
}

void dae::PositionComponent::SetPosition(const glm::vec3 & pos)
{
	m_Transform.SetPosition(pos);
}

void dae::PositionComponent::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x,y,z);
}

void dae::PositionComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime); 
}
