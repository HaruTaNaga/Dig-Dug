#pragma once
#include "ComponentsH.h"

namespace dae {
	class OrientationComponent; 
	class PositionComponent; 
	class CommandComponent;
	class HoseComponent; 
	class  PumpComponent : public BaseComponent {

	public: 
		PumpComponent(HoseComponent & hose, OrientationComponent & orientationComp, PositionComponent & positionComp,CommandComponent & eventGenComponent);
		virtual ~PumpComponent() {};
		
		OrientationComponent & m_OrientationComp; 
		PositionComponent & m_PositionComp; 
		CommandComponent & m_EventGenComponent; 

		void NotifyOnPumpLaunch();
		void NotifyOnPumpEnd();
		void NotifyOnPumpHit(); 
		void NotifyOnPumping(); 

		HoseComponent & m_Hose;
	};
}