﻿#include "MiniginPCH.h"
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
#include "EventFactory.h"
#include <DbgHelp.h>
#include "TextureManager.h"
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
	m_Renderer = new Renderer(); 
	//m_Renderer = ServiceLocator::GetRenderer();
	m_Renderer->Init(window, m_SceneManager);
	ServiceLocator::InitRenderer(m_Renderer);


	ServiceLocator::InitPhysicsManager(new PhysicsManager()); 


	ServiceLocator::InitInputManager(new InputManager());
	m_InputManager = ServiceLocator::GetInputManager(); 

	ServiceLocator::InitMapManager(new MapManager());
	m_MapManager = ServiceLocator::GetMapManager(); 

	ServiceLocator::InitEventFactory(new EventFactory());
	ServiceLocator::InitTextureManager(new TextureMananager());
	m_SceneLoader = new SceneLoader(); 
	ServiceLocator::InitResourceManager(new ResourceManager());
	//ServiceLocator::InitResourceManager(new ResourceManager()); 
	//m_MapManager = ServiceLocator::GetMapManager();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const

{
	//m_MapManager->LoadMap(Levels::Level1);
	//m_SceneLoader->InitialiseNewScene(Levels::Level1);

	m_MapManager->LoadMap(Levels::DEMO);
	m_SceneLoader->InitialiseNewScene(Levels::DEMO);
	


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
	ServiceLocator::GetResourceManager()->Init("../Data/");
	float deltaTime = 0.0f;
	LoadGame();
	std::cout << sizeof(std::reference_wrapper<MoveComponent>); 

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
