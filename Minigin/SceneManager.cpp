#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(const float deltaTime) 
{

		m_Scenes[m_ActiveSceneIndex]->Update(deltaTime);
	
}

void dae::SceneManager::Render()
{

		m_Scenes[m_ActiveSceneIndex]->Render();
	
}

std::shared_ptr<dae::Scene>  dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveSceneIndex = (int)m_Scenes.size() - 1; 
	return scene;
}
