#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "PumpComponent.h"

dae::PumpComponent::PumpComponent(HoseComponent & hose, OrientationComponent & orientationComp, PositionComponent & positionComp, CommandComponent & cmdComponent)
	: m_Hose(hose), m_OrientationComp(orientationComp), m_PositionComp(positionComp), m_CommandComponent(cmdComponent)

{
	m_Hose.m_PumpComp = this; 
}

void dae::PumpComponent::NotifyOnPumpLaunch()
{
	m_Hose.NotifyOnPumpLaunch(m_PositionComp, m_OrientationComp);
}

void dae::PumpComponent::NotifyOnPumpEnd()
{
	m_Hose.NotifyOnPumpEnd(); 
}

void dae::PumpComponent::NotifyOnPumpHit()
{
	m_CommandComponent.StartPumpingEnemy();
}

void dae::PumpComponent::NotifyOnPumping()
{
	m_CommandComponent.PlayerPumping();
	m_Hose.NotifyOnPlayerPumping();
}
