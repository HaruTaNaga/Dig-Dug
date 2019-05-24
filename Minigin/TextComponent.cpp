#pragma once
#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

#include "ServiceLocator.h"

dae::TextComponent::TextComponent(TextureComponent & texc, std::string text, std::shared_ptr<Font> font, bool updateEveryFrame) 
	: m_TextureComponent(texc), mText(text), m_NeedsUpdate(true), m_UpdatedEveryFrame(updateEveryFrame), mFont(font)
{
	m_Renderer = ServiceLocator::GetRenderer(); 
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_NeedsUpdate || m_UpdatedEveryFrame)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		//TTF_SizeText()
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);

		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(m_Renderer->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextureComponent.SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false; 
		
	}
}

void dae::TextComponent::SetText(std::string text)
{
	mText = text;
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
		//TTF_SizeText()
	const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);

	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(m_Renderer->GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextureComponent.SetTexture(std::make_shared<Texture2D>(texture));
	m_NeedsUpdate = false;
}
