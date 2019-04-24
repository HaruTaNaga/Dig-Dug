#pragma once
#include "ComponentsH.h"
namespace dae {
	class PumpComponent;
	class EventGenComponent; 
	class OrientationComponent; 
	class MoveComponent; 
	class HoseComponent : public BaseComponent {
	public: 
		HoseComponent(EventGenComponent & eventGenComp, PositionComponent & posComp,OrientationComponent & m_OrientationComp, MoveComponent & movComp);
		virtual ~HoseComponent() {};
		void Update(float) override;
		PumpComponent * m_PumpComp; 
		EventGenComponent & m_EventGenComp;
		PositionComponent & m_PositionCmp; 
		PositionComponent * m_PlayerPositionCmp;
		OrientationComponent * m_PlayerOrientationCmp; 
		MoveComponent & m_MoveComponent; 
		void NotifyOnPumpLaunch(PositionComponent & posCmp, OrientationComponent & oriCmp) ;
		void NotifyOnPumpEnd(); 
		void NotifyOnPumpHit();
		void NotifyOnPlayerPumping();

		void ConnectEnemy(GameObject * enemy) { m_ConnectedEnemy = enemy; }
		GameObject  * m_ConnectedEnemy;
		OrientationComponent & m_OrientationComp;
		bool hasConnected = false; 
		int m_TickCounter = 0;
		bool m_IsBeingFired = false; 

	};
}