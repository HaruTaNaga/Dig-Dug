#pragma once
#include "ComponentsH.h"
#include "Font.h"

namespace  dae {
	class TextComponent;
	class TextureComponent;
	class HpUiComponent : public BaseComponent
	{
	private:

		HpUiComponent();
	public:
		HpUiComponent(TextComponent & texc);
		//	: m_TextComponent(texc), m_Hp(3) {};

		virtual ~HpUiComponent() {};
		void Update(float ) override {} ;
		HpUiComponent(const HpUiComponent& other) = delete;
		HpUiComponent(HpUiComponent&& other) = delete;
		HpUiComponent& operator=(const HpUiComponent& other) = delete;
		HpUiComponent& operator=(HpUiComponent&& other) = delete;
		void NotifyHpChanged(int hp);// { m_Hp = hp; }
		int m_Hp;
		TextComponent & m_TextComponent;
	};

}

