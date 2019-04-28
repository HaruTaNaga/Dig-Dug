#include "MiniginPCH.h"
#include "FallComponent.h"
#include "ServiceLocator.h"
#include "MapTile.h"
#include "ComponentsH.h"
dae::FallComponent::FallComponent(PositionComponent & posCmp, MoveComponent & MovComp, CollisionComponent & ColCmp) : m_PositionComponent(posCmp), m_MoveComponent(MovComp), m_CollisonComponent(ColCmp)
{
	m_PhysicsManager = ServiceLocator::GetPhysicsManager(); 
	m_MapManager = ServiceLocator::GetMapManager(); 

}

dae::FallComponent::~FallComponent()
{
}

void dae::FallComponent::Update(float )
{
	if (m_HasFallen) return;  


	auto pos = m_PositionComponent.GetPosition(); 

	pos.y += 32;

	auto & tile = m_MapManager->GetTileFromCoord((int)round(pos.x),(int) round(pos.y)); 
	if (m_OriginalTile == nullptr) m_OriginalTile = &tile; 
	if (!m_IsFalling)
	{
	if (tile.m_IsTraversible)
	{
		if (m_PhysicsManager->CheckPlayerCollision(Vec2(pos.x, pos.y)) != CollisionFlags::Player)
			m_StartFalling = true;
	}

	if (m_StartFalling)
		m_FallDelay++; 

	if (m_FallDelay > 60)
	{
		m_CollisonComponent.m_CollisionCategoryFlags = CollisionFlags::FallingRock;
		m_IsFalling = true; 
		m_MoveComponent.SetVelocity(0, 100);
	}
	}
	else
	{
		if (!tile.m_IsTraversible || (&tile != m_OriginalTile && (!tile.m_UpEdge->IsPassable )))
		{
			m_HasFallen = true;  
			m_MoveComponent.SetVelocity(0, 0);
		}
	}



}
