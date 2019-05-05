#pragma once


struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	
	class Texture2D;
	class SceneManager; 
	class BaseRenderComponent; 
	class MapManager;
	class Renderer final
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window, SceneManager* m_SceneManager);
		void Setup() ;

		void Render();
		void Destroy();
		void RenderAnimation(const Texture2D& texture, float x, float y, float xUv, float yUv) const;
		void RenderAnimation(const Texture2D& texture, float x, float y, float xUv, float yUv, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
	
		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
		SceneManager * m_SceneManager; 
		std::vector<BaseRenderComponent *> m_RenderComponents; 
		MapManager * m_MapManager; 
	};
}

