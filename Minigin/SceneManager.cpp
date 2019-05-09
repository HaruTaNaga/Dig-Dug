#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"

void dae::SceneManager::Update(const float deltaTime) 
{

		m_Scenes[m_ActiveSceneIndex]->Update(deltaTime);
	
}

void dae::SceneManager::Render()  const                
{

		m_Scenes[m_ActiveSceneIndex]->Render();
	
}

void dae::SceneManager::SetActiveScene(const int id)
{
	if (id < 0 || id > m_Scenes.size() - 1)  return; 

	 m_ActiveSceneIndex = id; 
	 ServiceLocator::GetRenderer()->Setup();  

}

std::shared_ptr<dae::Scene>  dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveSceneIndex = (int)m_Scenes.size() - 1; 
	return scene;
}

dae::SceneManager::~SceneManager()
{
	     
}
