#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "ServiceLocator.h"
dae::CollisionComponent::CollisionComponent(
	PositionComponent & posC, 
	OrientationComponent & oriC, 
	bool isPlayer  = false, 
	bool isRock = false, 
	bool isenemy = false) 
	: 
	m_IsPlayerCollisionFlag(isPlayer),
	m_IsRockCollisionFlag(isRock), 
	m_IsEnemyCollisionFlag(isenemy),
	m_PositionComponent(posC), 
	m_OrientationComponent(oriC)
{
	m_PhysicsManager = ServiceLocator::GetPhysicsManager(); 
}
dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(float )
{

}
