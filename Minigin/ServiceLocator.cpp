#include "MiniginPCH.h"

#include "ServiceLocator.h"


 dae::Renderer * dae::ServiceLocator::m_Renderer = nullptr;
 dae::SceneManager * dae::ServiceLocator::m_SceneManager = nullptr;
 dae::PhysicsManager *  dae::ServiceLocator::m_PhysicsManager = nullptr;
 dae::InputManager *  dae::ServiceLocator::m_InputManager = nullptr;