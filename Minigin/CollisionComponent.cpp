#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"
dae::CollisionComponent::CollisionComponent(CollisionFlags flags, CommandComponent & eventGenComponent)
	: m_CommandComponent(eventGenComponent),
	m_CollisionCategoryFlags(flags)
{
	m_PhysicsManager = ServiceLocator::GetPhysicsManager(); 
}


void dae::CollisionComponent::Update(float )
{

}

bool dae::CollisionComponent::CheckCollision(dae::Vec2 pos)
{
	if (m_CollisionCategoryFlags == CollisionFlags::Hose && m_CommandComponent.m_HoseComponent->m_IsBeingFired)
	{
		auto position = m_CommandComponent.m_HoseComponent->m_PositionCmp.GetPosition();
		auto orientation = m_CommandComponent.m_HoseComponent->m_OrientationComp.GetOrientation();
		auto size = Vec2(16, 16);
		switch (orientation)
		{
		case Right:
			position.x += m_CommandComponent.m_HoseComponent->m_TickCounter;
			break; 
		case Bottom: 
			position.y += m_CommandComponent.m_HoseComponent->m_TickCounter;
			break;
		case  Left: 
		case Top: 
			break; 

		};
		auto pair = m_PhysicsManager->CheckHoseCollision(Vec2(position.x, position.y), size);
		switch (pair.first)
		{
		case Enemy:
		case Static: 
			m_CommandComponent.HoseHit(pair.second);
			return true;
			break;
		
		
		}
		return false;
	} 
	else if (m_CanCollide && m_CollisionCategoryFlags == CollisionFlags::Player)
	{
		switch (m_PhysicsManager->CheckPlayerCollision(pos))
		{
		case Enemy:
			m_CommandComponent.Death();
		case Static:

			return true;
			break;
		case Player:
		default:
			return false;
			break;
		};
	}
	else if (m_CanCollide && m_CollisionCategoryFlags == CollisionFlags::Enemy)
	{
		switch (m_PhysicsManager->CheckPlayerCollision(pos))
		{
		case FallingRock:

			m_CommandComponent.EnemyCrushed();
		case Static:

			return true;
			break;
		case Player:
		default:
			return false;
			break;
		};
	}
	return false; 
}
