#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "MapManager.h"
#include  "ServiceLocator.h"
#include "SceneManager.h"
void dae::Renderer::Init(SDL_Window * window, SceneManager * sceneManager)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	m_SceneManager = sceneManager;
	//m_MapManager = ServiceLocator::GetMapManager(); 
}

void dae::Renderer::Render()
{
	/* Select the color for drawing. It is set to red here. */
	SDL_SetRenderDrawColor(mRenderer, 10, 20, 10, 255);

	/* Clear the entire screen to our selected color. */


	SDL_RenderClear(mRenderer);
	//m_ServiceLocator.GetSceneManager()->Render(); 
	m_SceneManager->Render();
	ServiceLocator::GetMapManager()->Render();
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
