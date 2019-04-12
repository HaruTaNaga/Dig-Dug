#include "MiniginPCH.h"
#include "CollisionComponent.h"
dae::CollisionComponent::CollisionComponent(std::shared_ptr<GameObject> owner, PositionComponent & posC, bool isPlayer  = false, bool isRock = false, bool isenemy = false) 
	: BaseComponent(owner), m_IsPlayerCollisionFlag(isPlayer), m_IsRockCollisionFlag(isRock), m_IsEnemyCollisionFlag(isenemy), m_PositionComponent(posC)
{

}
dae::CollisionComponent::~CollisionComponent()
{
}
