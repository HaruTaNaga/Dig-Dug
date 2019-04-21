#include "MiniginPCH.h"
#include "OrientationComponent.h"




dae::OrientationComponent::~OrientationComponent()
{
}

void dae::OrientationComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto vel = m_MoveComponent.AdjustedVelocity; 
	if (vel.x > 0)
		m_Orientation = Orientation::Right; 
	if (vel.x < 0)
		m_Orientation = Orientation::Left; 
	if (vel.y > 0)
		m_Orientation = Orientation::Bottom;
	if (vel.y < 0)
		m_Orientation = Orientation::Top;

	//m_TextureComponent.SetTexture(m_Textures[m_Orientation]);

		
	
}
