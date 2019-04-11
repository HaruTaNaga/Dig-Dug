#include "MiniginPCH.h"
#include "PositionComponent.h"





const glm::vec3 & dae::PositionComponent::GetPosition()
{
	return mTransform.GetPosition(); 
}

void dae::PositionComponent::SetPosition(const glm::vec3 & pos)
{
	mTransform.SetPosition(pos); 
}

void dae::PositionComponent::SetPosition(float x, float y, float z)
{
	mTransform.SetPosition(x,y,z);
}

void dae::PositionComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime); 
}
