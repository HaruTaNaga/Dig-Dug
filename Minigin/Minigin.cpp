#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
//#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"	
#include "SceneLoader.h"
#include "MapManager.h"
#include  "ServiceLocator.h"
//#include "InputManager.h"
void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"dig dug" ,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		g_width,
		g_height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	ServiceLocator::InitSceneManager(new SceneManager());
	m_SceneManager = ServiceLocator::GetSceneManager();
	ServiceLocator::InitRenderer(new  Renderer());

	ServiceLocator::InitPhysicsManager(new PhysicsManager()); 
	m_Renderer = ServiceLocator::GetRenderer();
	m_Renderer->Init(window, m_SceneManager);

	ServiceLocator::InitInputManager(new InputManager());
	m_InputManager = ServiceLocator::GetInputManager(); 

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	MapManager::GetInstance().LoadMap(Levels::DEMO); 
	SceneLoader::GetInstance().InitialiseNewScene(Levels::DEMO);

}

void dae::Minigin::Cleanup()
{
	m_Renderer->Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	float deltaTime = 0.0f;
	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		while (doContinue)
		{
			doContinue = m_InputManager->ProcessInput();
			auto const currentTime = std::chrono::high_resolution_clock::now(); 
			deltaTime = std::chrono::duration<float>(currentTime - lastTime).count(); 
			lastTime = currentTime; 
			m_SceneManager->Update(deltaTime);
			m_Renderer->Render();
			
			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
