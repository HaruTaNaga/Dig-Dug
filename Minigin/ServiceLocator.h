#pragma once

#include "SceneManager.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "MapManager.h"
#include "EventFactory.h"
namespace  dae {

	class ServiceLocator {
	public: 
	
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
		static void InitEventFactory(dae::EventFactory * eventFactory)
		{
			m_EventFactory.reset(eventFactory);
		}
		static dae::Renderer * GetRenderer() { return m_Renderer.get(); }
		static dae::SceneManager * GetSceneManager() { return m_SceneManager.get(); }
		static dae::PhysicsManager * GetPhysicsManager() { return m_PhysicsManager.get(); }
		static dae::InputManager * GetInputManager() { return m_InputManager.get(); }
		static dae::MapManager * GetMapManager() { return m_MapManager.get(); }
		static dae::EventFactory * GetEventFactory() { return m_EventFactory.get(); }	
	
	private:

		static std::unique_ptr<dae::Renderer>  m_Renderer; 
		static std::unique_ptr<dae::SceneManager> m_SceneManager;
		static std::unique_ptr<dae::PhysicsManager> m_PhysicsManager;
		static std::unique_ptr<dae::InputManager> m_InputManager;
		static std::unique_ptr<dae::MapManager> m_MapManager;
		static std::unique_ptr<dae::EventFactory> m_EventFactory;
	};
}