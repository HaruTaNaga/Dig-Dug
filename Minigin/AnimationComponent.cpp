#include "MiniginPCH.h"
#include "AnimationComponent.h"

void dae::AnimationComponent::Update(float )
{
	
	auto anim = m_Animations[m_ActiveAnimationId]; 
	if (++m_CurrentTickCounter >= anim.m_TickDuration)
	{
		m_CurrentTickCounter = 0;
		m_CurrentFrame = m_CurrentFrame + 1;
		if (m_CurrentFrame >= anim.m_AmountOfFrames)
			m_CurrentFrame = 0;


	}

}
