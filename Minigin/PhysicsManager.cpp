#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "PhysicsManager.h"
#include "ServiceLocator.h"
#include "Scene.h"
#include "GameObject.h"
#include "SceneObject.h"
#include  "glm\vec3.hpp"
dae::PhysicsManager::PhysicsManager()
{
	auto sceneManager = ServiceLocator::GetSceneManager(); 
	UNREFERENCED_PARAMETER(sceneManager);
}

void dae::PhysicsManager::InitActiveComponents()
{
	auto sceneMngr = ServiceLocator::GetSceneManager(); 
	auto scene = sceneMngr->GetActiveScene(); 
	auto sObjects = scene->GetSceneObjects(); 
	for (auto sObj : sObjects)
	{
		GameObject * gObj = dynamic_cast<GameObject *> (sObj.get()); 
		if (gObj != nullptr)
		{
			auto cComp = gObj->GetComponent<CollisionComponent>();
			if (cComp == nullptr)
				return; 
			auto pComp = static_cast<PositionComponent *>(gObj->GetComponent<PositionComponent>());
			m_Pair_PosComp_GameObj.push_back({ pComp,gObj });


		}
	}

}

dae::CollisionFlags dae::PhysicsManager::CheckPlayerCollision(dae::Vec2 pos)
{
	
	
	auto pos1 = pos;
	auto Box1 = Box((float)pos1.x + 16, (float)pos1.y + 16);
	for (auto pair : m_Pair_PosComp_GameObj)
	{
		auto posComp2 = pair.first;
		if (posComp2->GetPosition().x == pos1.x && posComp2->GetPosition().y == pos1.y)
			continue;
		auto pos2 = posComp2->GetPosition();
		auto Box2 = Box((float)pos2.x + 16, (float)pos2.y + 16);
		if (CheckBoxesIntersect(Box1,Box2))
		return static_cast<CollisionComponent *>(pair.second->GetComponent<CollisionComponent>())->m_CollisionCategoryFlags;

	}
	return NoCollision;
}
