#pragma once
#include  "ComponentsH.h"

namespace dae {

	class HpComponent; 
	class DeathComponent : public  BaseComponent {
	public:
		DeathComponent(HpComponent & hpComponent) : m_HpComponent(hpComponent) {};
		virtual ~DeathComponent() {}; 
		void Update(float ) override {};
		void NotifyOnDeath() ;
		bool HasDied() { return m_HasDied; }
		bool m_HasDied = false;

		HpComponent & m_HpComponent; 
	};

}