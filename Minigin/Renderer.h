#pragma once
#include "Singleton.h"
//#include  "ServiceLocator.h"
struct SDL_Window;
struct SDL_Renderer;
//#include "MapManager.h"
namespace dae
{
	//class ServiceLocator; 
	class Texture2D;
	class SceneManager; 
	//class MapManager;
	class Renderer final //: public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window, SceneManager* m_SceneManager);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		//ServiceLocator m_ServiceLocator; 
		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
		SceneManager * m_SceneManager; 
		//MapManager * m_MapManager; 
	};
}

