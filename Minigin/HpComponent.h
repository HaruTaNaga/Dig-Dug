#pragma once
#include "BaseComponent.h"
namespace dae {


	class HpComponent : public  BaseComponent {
	public:

		HpComponent(int hp = 3): m_Hp(hp){};
		~HpComponent() {};
		void Update(float deltaTime) override;
		void NotifyOnDeath();

		int m_Hp;

	};

}