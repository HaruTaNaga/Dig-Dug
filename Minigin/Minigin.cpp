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
	ServiceLocator::InitEventFactory(new CommandFactory());
	ServiceLocator::InitTextureManager(new TextureMananager());

	

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const

{
	//m_SceneLoader->InitialiseNewScene(Levels::Level1);

	m_SceneLoader->InitialiseNewScene(Levels::DEMO);
	
	//m_MapManager->LoadMap(Levels::Level1);
	


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
