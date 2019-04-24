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


void dae::CollisionComponent::Update(float )
{

}

bool dae::CollisionComponent::CheckCollision(dae::Vec2 pos)
{
	if (m_CollisionCategoryFlags == CollisionFlags::Hose && m_EventGenComponent.m_HoseComponent->m_IsBeingFired)
	{
		auto position = m_EventGenComponent.m_HoseComponent->m_PositionCmp.GetPosition(); 
		auto orientation = m_EventGenComponent.m_HoseComponent->m_OrientationComp.GetOrientation(); 
		auto size = Vec2(16, 16);

		switch (orientation)
		{

		case Right:
			//size = Vec2(16, 16);
			position.x += m_EventGenComponent.m_HoseComponent->m_TickCounter;
			//position.y += 16; 
			break; 
		case Bottom: 
			//size = Vec2(16, 16);
			position.y += m_EventGenComponent.m_HoseComponent->m_TickCounter;
			//position.x +=16;
			break;
		case  Left: 
			//size = Vec2(16, 16);
			//position.y -= 16;
			//position.y += 16;
			break; 
		case Top: 
			//size = Vec2(16, 16);
			//position.x += 16;
			//position.y -= 32; 
			break; 

		};
		auto pair = m_PhysicsManager->CheckHoseCollision(Vec2(position.x, position.y), size);
		switch (pair.first)
		{
		case Enemy:
		case Static: 
			m_EventGenComponent.GenerateHoseHitEvent(pair.second);
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
	else if (m_CanCollide && m_CollisionCategoryFlags == CollisionFlags::Enemy)
	{
		switch (m_PhysicsManager->CheckPlayerCollision(pos))
		{
		case FallingRock:

			m_EventGenComponent.GenerateEnemyCrushedEvent();
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
