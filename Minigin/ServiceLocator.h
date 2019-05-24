#pragma once

#include "SceneManager.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "MapManager.h"
#include "CommandFactory.h"
#include "TextureManager.h"
//#include "SceneLoader.h"
#include "ResourceManager.h"
#include "AiManager.h"
#include "EnemyManager.h"
#include  "ScoreManager.h"
namespace  dae {
	class AiManager; 
	class SceneLoader;
	class EnemyManager; 
	class ServiceLocator {
	public: 
	
		~ServiceLocator()
		{

		};
		static void Cleanup()
		{
			m_Renderer.reset(); 
			m_SceneManager.reset();
			m_PhysicsManager.reset();
			m_InputManager.reset();
			m_MapManager.reset();
			m_CommandFactory.reset();
			m_TextureManager.reset();
			m_ResourceManager.reset();

		}
		static void InitRenderer(dae::Renderer * renderer) 
		{
			m_Renderer.reset(renderer);
		}
		static void InitSceneManager(dae::SceneManager * scenemanager) {
			m_SceneManager.reset(scenemanager);
		}
		static void InitPhysicsManager(dae::PhysicsManager * physicsmanager)
		{
			m_PhysicsManager.reset(physicsmanager);
		}
		static void InitInputManager(dae::InputManager * inputmanager)
		{
			m_InputManager.reset(inputmanager); 
		}
		static void InitMapManager(dae::MapManager * mapmanager) 
		{ 
			m_MapManager.reset(mapmanager); 
		}
		static void InitCommandFactory(dae::CommandFactory * commandFactory)
		{
			m_CommandFactory.reset(commandFactory);
		}
		static void InitTextureManager(dae::TextureMananager * texmgr)
		{
			m_TextureManager.reset(texmgr);
		}
		static void InitAiManager(dae::AiManager * aiMngr)
		{
			m_AiManager.reset(aiMngr);
		}
		/*
		static void InitSceneLoader(dae::SceneLoader * sceneLoader)
		{
			m_SceneLoader.reset(sceneLoader);
		}	*/
		
		static void InitResourceManager(dae::ResourceManager * resourceManager)
		{
			m_ResourceManager.reset(resourceManager);
		}
		static void InitEnemyManager(dae::EnemyManager * enemyManager)
		{
			m_EnemyManager.reset(enemyManager);
		}
		static void InitScoreManager(dae::ScoreManager * scoreManager)
		{
			m_ScoreManager.reset(scoreManager);
		}
		static dae::Renderer * GetRenderer() { return m_Renderer.get(); }
		static dae::SceneManager * GetSceneManager() { return m_SceneManager.get(); }
		static dae::PhysicsManager * GetPhysicsManager() { return m_PhysicsManager.get(); }
		static dae::InputManager * GetInputManager() { return m_InputManager.get(); }
		static dae::MapManager * GetMapManager() { return m_MapManager.get(); }
		static dae::CommandFactory * GetCommandFactory() { return m_CommandFactory.get(); }	
		static dae::TextureMananager * GetTextureManager() { return m_TextureManager.get(); }
		//static dae::SceneLoader * GetSceneLoader() { return m_SceneLoader.get(); }
		static dae::ResourceManager * GetResourceManager() { return m_ResourceManager.get(); }
		static dae::AiManager * GetAiManager() { return m_AiManager.get(); }
		static dae::EnemyManager * GetEnemyManager() { return m_EnemyManager.get(); }
		static dae::ScoreManager * GetScoreManager() { return m_ScoreManager.get(); }

	private:

		static std::unique_ptr<dae::Renderer>  m_Renderer; 
		static std::unique_ptr<dae::SceneManager> m_SceneManager;
		static std::unique_ptr<dae::PhysicsManager> m_PhysicsManager;
		static std::unique_ptr<dae::InputManager> m_InputManager;
		static std::unique_ptr<dae::MapManager> m_MapManager;
		static std::unique_ptr<dae::CommandFactory> m_CommandFactory;
		static std::unique_ptr<dae::TextureMananager> m_TextureManager;
		//static std::unique_ptr<dae::SceneLoader> m_SceneLoader;
		static std::unique_ptr<dae::ResourceManager> m_ResourceManager;
		static std::unique_ptr<dae::AiManager	> m_AiManager;
		static std::unique_ptr<dae::EnemyManager	> m_EnemyManager;
		static  std::unique_ptr<dae::ScoreManager> m_ScoreManager; 

	};
}