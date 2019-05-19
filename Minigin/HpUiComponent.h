#pragma once
#include "ComponentsH.h"
#include "Font.h"

namespace  dae {
	class TextComponent;
	class TextureComponent;
	class IObserver; 

	class HpUiComponent : public BaseComponent
	{
	private:

		HpUiComponent();
	public:
		HpUiComponent(TextComponent & texc);
	

		virtual ~HpUiComponent() {};
	
		HpUiComponent(const HpUiComponent& other) = delete;
		HpUiComponent(HpUiComponent&& other) = delete;
		HpUiComponent& operator=(const HpUiComponent& other) = delete;
		HpUiComponent& operator=(HpUiComponent&& other) = delete;
		void NotifyHpChanged(int hp);
		int m_Hp;
		TextComponent & m_TextComponent;
		
	};

}

