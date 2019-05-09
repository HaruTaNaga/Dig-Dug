#include "MiniginPCH.h"
#include "AnimationComponent.h"

void dae::AnimationComponent::Update(float )
{
	if (FreezeAnimation) return; 
	auto anim = m_Animations[m_ActiveAnimationId]; 
	if (++m_CurrentTickCounter >= anim.m_TickDuration)
	{
		m_CurrentTickCounter = 0;
		
		if (++m_CurrentFrame >= anim.m_AmountOfFrames)
			m_CurrentFrame = 0;


	}

}

void dae::AnimationComponent::GoToNextFrame()
{
	m_CurrentFrame = m_CurrentFrame + 1;
	if (++m_CurrentFrame >= m_Animations[m_ActiveAnimationId].m_AmountOfFrames)
		m_CurrentFrame = 0;
}
