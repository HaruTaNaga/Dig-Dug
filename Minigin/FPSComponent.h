#pragma once
#include "ComponentsH.h"
#include "Font.h"

namespace  dae {
	class TextComponent; 
	class TextureComponent;
	class FPSComponent :  public BaseComponent
	{
	private: 

		FPSComponent();
	public:
		FPSComponent(TextComponent & texc)
			: m_TextComponent(texc) {};
		
		~FPSComponent();
		void Update(float deltaTime) override;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		TextComponent & m_TextComponent;
	};

}

