#include "MiniginPCH.h"
#include "FireBreathComponent.h"
#include "FireComponent.h"
#include "PositionComponent.h"

#include "FygarOrientationComponent.h"
dae::FireBreathComponent::FireBreathComponent(FygarOrientationComponent & oriComp, FireComponent & fireComp, PositionComponent & posComp)
	:
	m_FireComponent(fireComp), 
	m_PositionComponent(posComp), 
	m_OrientationComponent(oriComp)
{
}
void dae::FireBreathComponent::BreathFire()
{
	const auto pos = m_PositionComponent.GetPosition();
	bool flipped = false; 
	if (m_OrientationComponent.GetOrientation() == FygarOrientation::FygarLeft)
		flipped = true;  
	m_FireComponent.Fire(flipped, Vec2(pos.x, pos.y));

}

void dae::FireBreathComponent::EndFire()
{
	m_FireComponent.EndFire(); 

}
