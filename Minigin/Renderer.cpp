#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "MapManager.h"
#include  "ServiceLocator.h"
#include "SceneManager.h"
#include  "Scene.h"
#include "ComponentsH.h"
void dae::Renderer::Init(SDL_Window * window, SceneManager * sceneManager)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	m_SceneManager = sceneManager;
	
}

void dae::Renderer::Setup()
{
	m_RenderComponents.clear(); 
	m_MapManager = ServiceLocator::GetMapManager();
	auto gameObjects = m_SceneManager->GetActiveScene()->GetSceneObjects(); 
	for (auto sObj : gameObjects)
	{
		auto gObj = static_cast<GameObject *>(sObj.get()); 
		auto aniCmp = gObj->GetComponent<AnimatedRenderComponent>(); 
		auto texCmp = gObj->GetComponent<RenderComponent>(); 
		if (aniCmp != nullptr)
			m_RenderComponents.push_back(static_cast<BaseRenderComponent *>(aniCmp)); 
		if (texCmp != nullptr)
			m_RenderComponents.push_back(static_cast<BaseRenderComponent *>(texCmp));
	}

}

void dae::Renderer::Render()
{
	/* Select the color for drawing. It is set to red here. */
	SDL_SetRenderDrawColor(mRenderer, 10, 20, 10, 255);

	/* Clear the entire screen to our selected color. */


	SDL_RenderClear(mRenderer);
	//m_ServiceLocator.GetSceneManager()->Render(); 
	for (auto cmp : m_RenderComponents)
		cmp->Render(); 

	//m_SceneManager->Render();
	m_MapManager->Render();
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

void dae::Renderer::RenderAnimation(const Texture2D & texture, float x, float y, float xUv, float yUv, float width, float height) const
{
	//Render an animation with certain width and height
	int uvX = static_cast<int>(xUv);
	int uvY = static_cast<int>(yUv);
	SDL_Rect dst;
	dst.x = static_cast<int>(x) - uvX;
	dst.y = static_cast<int>(y) - uvY;
	SDL_Rect clip;
	clip.x = dst.x + uvX;
	clip.y = dst.y + uvY;
	clip.w = static_cast<int>(width);
	clip.h = static_cast<int>(height);
	auto tex = texture.GetSDLTexture();
	SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderSetClipRect(GetSDLRenderer(), &clip);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	SDL_RenderSetClipRect(GetSDLRenderer(), NULL);
}
void dae::Renderer::RenderAnimation(const Texture2D & texture, float x, float y, float xUv, float yUv) const
{
	int uvX = static_cast<int>(xUv);
	int uvY = static_cast<int>(yUv);
	SDL_Rect dst;
	dst.x = static_cast<int>(x) - uvX;
	dst.y = static_cast<int>(y) - uvY;
	SDL_Rect clip;
	clip.x = dst.x + uvX;
	clip.y = dst.y + uvY;
	clip.h = 32;
	clip.w = 32;
	auto tex = texture.GetSDLTexture();
	SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderSetClipRect(GetSDLRenderer(), &clip);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	SDL_RenderSetClipRect(GetSDLRenderer(), NULL);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	auto uvX = 0; 
	auto uvY = 0; 
	SDL_Rect dst;
	dst.x = static_cast<int>(x) - uvX;
	dst.y = static_cast<int>(y) - uvY;

	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderSetClipRect(GetSDLRenderer(), &clip);
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
