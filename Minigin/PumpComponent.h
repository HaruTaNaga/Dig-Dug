#pragma once
#include "ComponentsH.h"

namespace dae {
	class OrientationComponent; 
	class PositionComponent; 
	class EventGenComponent;
	class HoseComponent; 
	class  PumpComponent : public BaseComponent {

	public: 
		PumpComponent(HoseComponent & hose, OrientationComponent & orientationComp, PositionComponent & positionComp,EventGenComponent & eventGenComponent);
		~PumpComponent() {};
		
		OrientationComponent & m_OrientationComp; 
		PositionComponent & m_PositionComp; 
		EventGenComponent & m_EventGenComponent; 

		void NotifyOnPumpLaunch();
		void NotifyOnPumpEnd();
		void NotifyOnPumpHit(); 
		void NotifyOnPumping(); 

		HoseComponent & m_Hose;
	};
}