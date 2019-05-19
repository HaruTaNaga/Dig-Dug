#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"
#include "FireComponent.h"
#include "PositionComponent.h"
dae::CollisionComponent::CollisionComponent(CollisionFlags flags, CommandComponent & eventGenComponent)
	: m_CommandComponent(eventGenComponent),
	m_CollisionCategoryFlags(flags)
{
	m_PhysicsManager = ServiceLocator::GetPhysicsManager(); 
}


void dae::CollisionComponent::Update(float )
{
	if (m_CollisionCategoryFlags == CollisionFlags::Fire)
	{
		auto pos = m_PositionComponent->GetPosition(); 

		//bool isFlipped = m_FireComponent->m_IsFlipped;
		int animationFrame = m_FireComponent->m_AnimationComponent.m_CurrentFrame;
		Box FireCollision = Box(pos.x, pos.y);
		FireCollision.width += 32 * animationFrame;
		//if (isFlipped)
		//	FireCollision.x -= 32 * ( animationFrame);
		auto p = m_PhysicsManager->CheckFireCollision(FireCollision);
		auto type = p.first;

		switch (type)
		{
		case Player:
			if (type == CollisionFlags::Player)
			{
				auto player = (p.second->GetComponent<CommandComponent>());
				p.second->GetComponent<CollisionComponent>()->m_CanCollide = false;
				player->Death();


			}
			break;
		};
	}
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
		auto  pair = m_PhysicsManager->CheckCollision(pos); 
		if (pair.first && pair.second->m_CanCollide)
		{
		switch (pair.second->m_CollisionCategoryFlags)
			{
			case Enemy:
			case  FallingRock:
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
