#pragma once
#include  "ComponentsH.h"

namespace dae {

	class EventGenComponent; 
	class HpComponent; 
	class DeathComponent : public  BaseComponent {
	public:
		DeathComponent(HpComponent & hpComponent, EventGenComponent & eventGenComponent) : m_HpComponent(hpComponent), m_EventGenComponent(eventGenComponent) {};
		~DeathComponent() {}; 
		void Update(float ) override {};
		void NotifyOnDeath() ;
		bool HasDied() { return m_HasDied; }
		bool m_HasDied = false;
		EventGenComponent & m_EventGenComponent; 
		HpComponent & m_HpComponent; 
	};

}