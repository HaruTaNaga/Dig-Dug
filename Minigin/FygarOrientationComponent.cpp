#include "MiniginPCH.h"
#include "FygarOrientationComponent.h"
#include "MoveComponent.h"
void dae::FygarOrientationComponent::Update(float )
{
	auto vel = m_MoveComponent.AdjustedVelocity;
	if (vel.x > 0)
		m_Orientation = FygarOrientation::FygarRight;
	if (vel.x < 0)
		m_Orientation = FygarOrientation::FygarLeft;
}
