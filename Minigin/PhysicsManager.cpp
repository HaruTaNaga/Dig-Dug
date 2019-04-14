#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "ServiceLocator.h"
dae::PhysicsManager::PhysicsManager()
{
	auto sceneManager = ServiceLocator::GetSceneManager(); 
	UNREFERENCED_PARAMETER(sceneManager);
}
