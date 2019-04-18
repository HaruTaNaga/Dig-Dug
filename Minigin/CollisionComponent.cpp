#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"

dae::CollisionComponent::CollisionComponent(CollisionFlags flags) 
	: 
	m_CollisionCategoryFlags(flags)
{
	m_PhysicsManager = ServiceLocator::GetPhysicsManager(); 
}
dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(float )
{

}

bool dae::CollisionComponent::CheckCollision(dae::Vec2 pos)
{
	switch (m_PhysicsManager->CheckPlayerCollision(pos))
	{
	case Static:
	case Enemy:
		return true;
		break;
	case Player: 
	default: 
		return false; 
		break;
	};
}
