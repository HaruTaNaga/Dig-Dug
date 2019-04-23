#include "MiniginPCH.h"
#include "HoseComponent.h"
#include "ComponentsH.h"
dae::HoseComponent::HoseComponent(EventGenComponent & eventGenComp, PositionComponent & posComp, OrientationComponent & oriCmp, MoveComponent & movComp)
	: m_EventGenComp(eventGenComp), m_PositionCmp(posComp), m_OrientationComp(oriCmp), m_MoveComponent(movComp)
{
}

void dae::HoseComponent::Update(float)
{
	if (hasConnected || !m_IsBeingFired)
		return;
	m_TickCounter++; 
	
	glm::vec3 pos; 
	auto ori = m_OrientationComp.GetOrientation();
	switch (ori)
	{
	case Top:
		 pos = m_PositionCmp.GetPosition();
		pos.y--;
		m_PositionCmp.SetPosition(pos);
		break; 
	case Left:
		 pos  = m_PositionCmp.GetPosition(); 
		pos.x--; 
		m_PositionCmp.SetPosition(pos); 
		break; 

	}
}

void dae::HoseComponent::NotifyOnPumpLaunch(PositionComponent & posCmp, OrientationComponent & oriCmp)
{
	m_PlayerPositionCmp = &posCmp;
	m_PlayerOrientationCmp = &oriCmp; 
	m_EventGenComp.GenerateHoseLaunchEvent(); 
	m_TickCounter = 0; 
	m_IsBeingFired = true; 
	hasConnected = false;

}

void dae::HoseComponent::NotifyOnPumpEnd()
{
	//m_MoveComponent.SetVelocity(0, 0);
	m_EventGenComp.GenerateHoseEndEvent(); 
	m_IsBeingFired = false; 
	hasConnected = false;
}

void dae::HoseComponent::NotifyOnPumpHit()
{
	hasConnected = true; 
	m_PumpComp->NotifyOnPumpHit();
	//m_MoveComponent.SetVelocity(0, 0);
	//m_EventGenComp.GenerateHoseHitEvent();
}

void dae::HoseComponent::NotifyOnPlayerPumping()
{
 static_cast<EventGenComponent*>(m_ConnectedEnemy->GetComponent<EventGenComponent>())->GenerateEnemyPumpedEvent();
	
}
