#pragma once

#include "SceneManager.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "InputManager.h"
namespace  dae {

	class ServiceLocator {
	public: 
		static void InitRenderer(dae::Renderer * renderer) {
			m_Renderer = renderer; 
		}
		static void InitSceneManager(dae::SceneManager * scenemanager) {
			m_SceneManager = scenemanager;
		}
		static void InitPhysicsManager(dae::PhysicsManager * physicsmanager)
		{
			m_PhysicsManager = physicsmanager; 
		}
		static void InitInputManager(dae::InputManager * inputmanager)
		{
			m_InputManager = inputmanager; 
		}
		static dae::Renderer * GetRenderer() { return m_Renderer; }
		static dae::SceneManager * GetSceneManager() { return m_SceneManager; }
		static dae::PhysicsManager * GetPhysicsManager() { return m_PhysicsManager; }
		static dae::InputManager * GetInputManager() { return m_InputManager; }
	private: 

		static dae::Renderer * m_Renderer; 
		static dae::SceneManager * m_SceneManager;
		static dae::PhysicsManager * m_PhysicsManager; 
		static dae::InputManager * m_InputManager; 

	};
}