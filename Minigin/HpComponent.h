#pragma once
#include "ComponentsH.h"
namespace dae {

	class HpUiComponent;  
	class HpComponent : public  BaseComponent {
	public:

		HpComponent(HpUiComponent & m_uicmp,  int hp = 3): m_Hp(hp), m_CurrentHp(hp), m_HpUiComp(m_uicmp) {};
		~HpComponent() {};
		void Update(float ) override {};
		void NotifyOnDeath();
		bool IsGameOver() { return m_Hp == 0;  }
		int m_CurrentHp; 
		int m_Hp;
		class HpUiComponent & m_HpUiComp; 
	};

}