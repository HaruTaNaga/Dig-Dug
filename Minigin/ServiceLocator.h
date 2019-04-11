#pragma once

#include "SceneManager.h"
#include "Renderer.h"
namespace  dae {

	class ServiceLocator {
	public: 
		static void InitRenderer(dae::Renderer * renderer) {
			m_Renderer = renderer; 
		}
		static void InitSceneManager(dae::SceneManager * scenemanager) {
			m_SceneManager = scenemanager;
		}
		static dae::Renderer * GetRenderer() { return m_Renderer; }
		static dae::SceneManager * GetSceneManager() { return m_SceneManager; }
	private: 

		static dae::Renderer * m_Renderer; 
		static dae::SceneManager * m_SceneManager;
	};
}