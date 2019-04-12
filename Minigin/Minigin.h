#pragma once

struct SDL_Window;
#include "ServiceLocator.h"
namespace dae
{
	class Renderer; 
	class SceneManager; 
	class ServiceLocator;  
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		
		dae::Renderer * m_Renderer; 
		dae::SceneManager * m_SceneManager; 
		

	
	};
}