#pragma once
#include "BaseComponent.h"
namespace dae {


	class HpComponent : public  BaseComponent {
	public:

		HpComponent(int hp = 3): m_Hp(hp), m_CurrentHp(hp) {};
		~HpComponent() {};
		void Update(float ) override {};
		bool NotifyOnDeath() { if (--m_Hp <= 0) return false; else return true; }
		int m_CurrentHp; 
		int m_Hp;

	};

}