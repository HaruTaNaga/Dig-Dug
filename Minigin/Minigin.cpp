#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
//#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "MapManager.h"
#include  "ServiceLocator.h"
#include "TextureManager.h"
#include "SceneLoader.h"
#include "AiManager.h"
#include <DbgHelp.h>


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


	m_SceneLoader = new SceneLoader();
	ServiceLocator::InitInputManager(new InputManager());
	m_InputManager = ServiceLocator::GetInputManager(); 
	ServiceLocator::InitSceneManager(new SceneManager());
	m_SceneManager = ServiceLocator::GetSceneManager();

	m_Renderer = new Renderer();
	m_Renderer->Init(window, m_SceneManager);
	ServiceLocator::InitRenderer(m_Renderer);

	ServiceLocator::InitResourceManager(new ResourceManager());
	ServiceLocator::InitMapManager(new MapManager());
	ServiceLocator::InitPhysicsManager(new PhysicsManager());
	ServiceLocator::InitCommandFactory(new CommandFactory());
	ServiceLocator::InitTextureManager(new TextureMananager());
	ServiceLocator::InitAiManager(new  AiManager()); 


	

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const

{
	m_SceneLoader->InitialiseNewScene(Levels::DEMO);
	m_SceneLoader->InitialiseNewScene(Levels::MenuLevel);
	m_SceneLoader->InitialiseNewScene(Levels::LevelSinglePlayer);
	m_SceneLoader->InitialiseNewScene(Levels::LevelCoop);
	m_SceneLoader->InitialiseNewScene(Levels::LevelVersus);

	ServiceLocator::GetSceneManager()->SetActiveScene(1);
	//m_MapManager->LoadMap(Levels::MenuLevel);
	


}

void dae::Minigin::Cleanup()
{
	m_Renderer->Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	ServiceLocator::Cleanup();
	delete m_SceneLoader;
}

//TODO: 


//end level on death
//get  killed by rock 
//score  system
//track score  id
//enemy fygar
//player fygar
//fire
//ai movement & pathfinding
//rock despawn 
//hose check map
//Observable Component & Renderable component  base classes 
//Ai movement / pathfinding 
 //fix Texture Manager  naming

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ServiceLocator::GetResourceManager()->Init("../Data/");
	float deltaTime = 0.0f;
	LoadGame();
	

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		while (doContinue)
		{
			doContinue = m_InputManager->ProcessInput();
			auto currentTime = std::chrono::high_resolution_clock::now(); 
			
			deltaTime = std::chrono::duration<float>(currentTime - lastTime).count(); 
			if (deltaTime > 5.0f)  deltaTime = 0.16f;
			lastTime = currentTime; 
			m_SceneManager->Update(deltaTime);
			m_Renderer->Render();
			
			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
