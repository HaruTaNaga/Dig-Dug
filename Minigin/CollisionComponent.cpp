#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"
dae::CollisionComponent::CollisionComponent(CollisionFlags flags, EventGenComponent & eventGenComponent)
	: m_EventGenComponent(eventGenComponent),
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
	case Enemy:
		m_EventGenComponent.GenerateDeathEvent(); 
	case Static:
	
		return true;
		break;
	case Player: 
	default: 
		return false; 
		break;
	};
}
