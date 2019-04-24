#pragma once
#include "ComponentsH.h"
#include <string>
#include "Font.h"
#include "ServiceLocator.h"
namespace dae {
	class TextureComponent; 
	class TextComponent :
		public BaseComponent
	{
	public:
		TextComponent() = delete;
		TextComponent(TextureComponent & texc, std::string text, std::shared_ptr<Font> font, bool updateEveryFrame = false );
		virtual ~TextComponent();
		void Update(float deltaTime) override;
	
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetText(std::string text) { mText = text; }
	private: 
		std::string mText; 
		std::shared_ptr<Font> mFont;
		TextureComponent & m_TextureComponent; 
		Renderer * m_Renderer; 

		//ServiceLocator m_ServiceLocator;
		bool m_NeedsUpdate = false , m_UpdatedEveryFrame = false;
	};
}

