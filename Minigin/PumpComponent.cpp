#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "PumpComponent.h"

dae::PumpComponent::PumpComponent(HoseComponent & hose, OrientationComponent & orientationComp, PositionComponent & positionComp, EventGenComponent & eventGenComponent)
	: m_Hose(hose), m_OrientationComp(orientationComp), m_PositionComp(positionComp), m_EventGenComponent(eventGenComponent)

{

}

void dae::PumpComponent::NotifyOnPumpLaunch()
{
	m_Hose.NotifyOnPumpLaunch(m_PositionComp, m_OrientationComp);
}

void dae::PumpComponent::NotifyOnPumpEnd()
{
	m_Hose.NotifyOnPumpEnd(); 
}