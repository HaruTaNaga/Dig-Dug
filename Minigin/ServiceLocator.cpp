#include "MiniginPCH.h"

#include "ServiceLocator.h"


std::unique_ptr < dae::Renderer> dae::ServiceLocator::m_Renderer = nullptr;
 std::unique_ptr < dae::SceneManager> dae::ServiceLocator::m_SceneManager = nullptr;
 std::unique_ptr < dae::PhysicsManager>  dae::ServiceLocator::m_PhysicsManager = nullptr;
 std::unique_ptr < dae::InputManager>  dae::ServiceLocator::m_InputManager = nullptr;
 std::unique_ptr < dae::MapManager>  dae::ServiceLocator::m_MapManager = nullptr;
 std::unique_ptr < dae::CommandFactory>  dae::ServiceLocator::m_EventFactory = nullptr;
 std::unique_ptr < dae::TextureMananager>  dae::ServiceLocator::m_TextureManager = nullptr;
 //std::unique_ptr < dae::SceneLoader>  dae::ServiceLocator::m_SceneLoader = nullptr;
 std::unique_ptr < dae::ResourceManager>  dae::ServiceLocator::m_ResourceManager = nullptr;