#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "GameObject.h"
#include  "SceneObject.h"
#include "AiManager.h"
#include "SceneLoader.h"
void dae::SceneManager::Update(const float deltaTime) 
{

		m_Scenes[m_ActiveSceneIndex]->Update(deltaTime);
		
}

void dae::SceneManager::Render()  const                
{

		m_Scenes[m_ActiveSceneIndex]->Render();
	
}
void dae::SceneManager::ResetActiveScene()
{
	m_Scenes[m_ActiveSceneIndex]->GetSceneObjects().clear(); 

	switch (m_ActiveSceneIndex)
	{
	case 2: 
		m_SceneLoader->ResetActiveScene(Levels::LevelSinglePlayer);
		break;
	case 3: 
		m_SceneLoader->ResetActiveScene(Levels::LevelVersus);
		break;
	case 4: 
		m_SceneLoader->ResetActiveScene(Levels::LevelCoop);
		break;

	}
}
dae::Scene * dae::SceneManager::GetActiveScene()
{
	 return m_Scenes[m_ActiveSceneIndex].get();
}
void dae::SceneManager::SetActiveScene(const int id)
{
	if (id < 0 || id > m_Scenes.size() - 1)  return; 

	 m_ActiveSceneIndex = id; 
	 ServiceLocator::GetMapManager()->SetActiveMap(id); 
	 ServiceLocator::GetPhysicsManager()->InitActiveComponents();
	 ServiceLocator::GetRenderer()->Setup();  
	 auto AiManager = ServiceLocator::GetAiManager(); 
	 AiManager->ClearTrackedPlayers(); 
	 for (auto it : m_Scenes[m_ActiveSceneIndex]->GetSceneObjects())
	 { 
		 auto gObj = dynamic_cast<GameObject *>(&*it);
		 if (gObj == nullptr) continue; 
		 auto CollisionCmp = gObj->GetComponent<CollisionComponent>();
		 if (CollisionCmp  != nullptr && CollisionCmp->m_CollisionCategoryFlags == Player)
			 AiManager->LinkNewPlayerPosCmp(gObj->GetComponent<PositionComponent>()); 
	
	 }
	
}

dae::SceneManager::SceneManager() :m_SceneLoader(std::make_unique<SceneLoader>())
{
}

dae::Scene *  dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveSceneIndex = (int)m_Scenes.size() - 1; 
	return scene.get();
}

dae::SceneManager::~SceneManager()
{
	     
}
