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
	m_Pair_PosComp_GameObj.clear();

	auto sceneMngr = ServiceLocator::GetSceneManager(); 
	auto scene = sceneMngr->GetActiveScene(); 
	auto sObjects = scene->GetSceneObjects(); 
	for (auto sObj : sObjects)
	{
		GameObject * gObj = static_cast<GameObject *> (sObj.get()); 
		if (gObj != nullptr)
		{
			auto cComp = gObj->GetComponent<CollisionComponent>();
			if (cComp == nullptr)
				continue;;
			auto pComp = (gObj->GetComponent<PositionComponent>());
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
		Box2.height = 16; Box2.width = 16;
		if (CheckBoxesIntersect(Box1, Box2))
		{  //could optimize this by changing pair into tuple with collisioncomp
			auto colComp = pair.second->GetComponent<CollisionComponent>();
			if (colComp->m_CanCollide)
				return (colComp->m_CollisionCategoryFlags); 
		}
			
	

	}
	return NoCollision;
}
std::pair<bool,dae::CollisionComponent *> dae::PhysicsManager::CheckCollision(dae::Vec2 pos)
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
		Box2.height = 16; Box2.width = 16;
		if (CheckBoxesIntersect(Box1, Box2))
		{  //could optimize this by changing pair into tuple with collisioncomp
			auto colComp = pair.second->GetComponent<CollisionComponent>();
			if (colComp->m_CanCollide)
				return {true,colComp };
		}



	}
	return { false, nullptr };
}
std::pair<dae::CollisionFlags,  dae::GameObject* > dae::PhysicsManager::CheckHoseCollision(dae::Vec2 pos, dae::Vec2 size)
{


	auto pos1 = pos;
	auto Box1 = Box((float)pos1.x , (float)pos1.y );
	Box1.height = (int)size.x; Box1.width = (int)size.y;
	for (auto pair : m_Pair_PosComp_GameObj)
	{
		auto posComp2 = pair.first;
		if (posComp2->GetPosition().x == pos1.x && posComp2->GetPosition().y == pos1.y)
			continue;
		auto pos2 = posComp2->GetPosition();
		auto Box2 = Box((float)pos2.x +16, (float)pos2.y +16 );
		Box2.height = 16; Box2.width = 16; 
	
		if (CheckBoxesIntersect(Box1, Box2))
		{
			auto type = (pair.second->GetComponent<CollisionComponent>())->m_CollisionCategoryFlags;
			if (type == CollisionFlags::Enemy)
			{
				auto enemy = (pair.second->GetComponent<CommandComponent>());
				enemy->EnemyHit();

			}
			return { type, pair.second };
		}
	}
	return { NoCollision, nullptr };
}
std::pair<dae::CollisionFlags, dae::GameObject* > dae::PhysicsManager::CheckFireCollision(Box b)
{


	
	//auto Box1 = b;
	for (auto pair : m_Pair_PosComp_GameObj)
	{
		auto posComp2 = pair.first;
		if (posComp2->GetPosition().x == b.x && posComp2->GetPosition().y == b.y)
			continue;
		auto pos2 = posComp2->GetPosition();
		auto Box2 = Box((float)pos2.x + 16, (float)pos2.y + 16);
		Box2.height = 16; Box2.width = 16;

		if (CheckBoxesIntersect(b, Box2))
		{
			auto cComp = pair.second->GetComponent<CollisionComponent>();
			auto type = cComp->m_CollisionCategoryFlags;
			if (cComp->m_CanCollide)
				return { type, pair.second };
		}
	}
	return { NoCollision, nullptr };
}

/*if (type == CollisionFlags::Player)
			{
				auto player = (pair.second->GetComponent<CommandComponent>());
				player->Death();
			}*/