#include "MiniginPCH.h"

#include "ServiceLocator.h"


std::unique_ptr < dae::Renderer> dae::ServiceLocator::m_Renderer = nullptr;
 std::unique_ptr < dae::SceneManager> dae::ServiceLocator::m_SceneManager = nullptr;
 std::unique_ptr < dae::PhysicsManager>  dae::ServiceLocator::m_PhysicsManager = nullptr;
 std::unique_ptr < dae::InputManager>  dae::ServiceLocator::m_InputManager = nullptr;
 std::unique_ptr < dae::MapManager>  dae::ServiceLocator::m_MapManager = nullptr;
 std::unique_ptr < dae::CommandFactory>  dae::ServiceLocator::m_CommandFactory = nullptr;
 std::unique_ptr < dae::TextureMananager>  dae::ServiceLocator::m_TextureManager = nullptr;
 std::unique_ptr < dae::ResourceManager>  dae::ServiceLocator::m_ResourceManager = nullptr;
 std::unique_ptr<dae::AiManager> dae::ServiceLocator::m_AiManager = nullptr;
 std::unique_ptr<dae::EnemyManager> dae::ServiceLocator::m_EnemyManager = nullptr;
 std::unique_ptr<dae::ScoreManager> dae::ServiceLocator::m_ScoreManager = nullptr;