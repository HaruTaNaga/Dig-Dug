#include "MiniginPCH.h"
#include "FireComponent.h"
#include "PositionComponent.h"
#include "AnimationComponent.h"

dae::FireComponent::FireComponent(PositionComponent & posComp, AnimationComponent & AniComp) :  m_AnimationComponent(AniComp), m_PositionComponent(posComp)
{
}

void dae::FireComponent::Update(float )
{
	m_TickCounter++; 
	if (m_TickCounter > 60 && m_IsFlipped)
	{
		auto pos = m_PositionComponent.GetPosition(); 
		pos.x -= 32; 
		m_PositionComponent.SetPosition(pos); 
		m_TickCounter = 0;
	}
}

void dae::FireComponent::Fire(bool isFlipped, dae::Vec2 Position)
{
	
	m_AnimationComponent.m_CurrentFrame = 0; 
	m_AnimationComponent.m_CurrentTickCounter = 0; 
	m_IsFlipped = isFlipped;  
	if (!m_IsFlipped)
	{ 
		Position.x += 32;
		m_AnimationComponent.m_ActiveAnimationId = 0;
	}
	else
	{
		Position.x -= 32;
		m_AnimationComponent.m_ActiveAnimationId = 1;  
	}

	m_PositionComponent.SetPosition(Position.x, Position.y, 0);
	m_TickCounter = 0; 

}

void dae::FireComponent::EndFire()
{
	m_PositionComponent.SetPosition(999, 999, 0);

}
