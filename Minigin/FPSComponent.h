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
		FPSComponent(std::shared_ptr<GameObject> owner, TextComponent & texc)
			: BaseComponent(owner), m_TextComponent(texc) {};
			//: TextComponent(owner, texc, "", font, true) {};
		~FPSComponent();
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::fpsComp; }
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		TextComponent & m_TextComponent;
	};

}

