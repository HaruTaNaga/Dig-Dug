#include "MiniginPCH.h"
#include "AnimationComponent.h"

void dae::AnimationComponent::Update(float )
{
	if (FreezeAnimation) return; 
	auto anim = m_Animations[m_ActiveAnimationId]; 
	if (++m_CurrentTickCounter >= anim.m_TickDuration)
	{
		m_CurrentTickCounter = 0;
		m_CurrentFrame = m_CurrentFrame + 1;
		if (m_CurrentFrame >= anim.m_AmountOfFrames)
			m_CurrentFrame = 0;


	}

}

void dae::AnimationComponent::CreateHoseAnimation(Vec2 uvR, Vec2 uvL, Vec2 uvB, Vec2 uvT)
{
	int width = 64;
	int height = 16;
	AnimationClip acRight(64, 1U);

	for (int i = 0; i < width; i++)
		acRight.AddClippedFrame(Vec2(uvR.x + (width - i), uvR.y), Vec2(i, height));
	m_Animations.push_back(acRight);

	AnimationClip acLeft(64, 1U);
	for (int i = 0; i < width; i++)
		acLeft.AddClippedFrame(Vec2(uvL.x, uvL.y), Vec2(i, height));
	m_Animations.push_back(acLeft);

	AnimationClip AcBot(64, 1U);
	for (int i = 0; i < width; i++)
		AcBot.AddClippedFrame(Vec2(uvB.x, uvB.y + (width - i)), Vec2(16, i));
	m_Animations.push_back(AcBot);

	AnimationClip acTop(64, 1U);
	for (int i = 0; i < width; i++)
		acTop.AddClippedFrame(Vec2(uvT.x, uvT.y), Vec2(16, i));
	m_Animations.push_back(acTop);
	m_ActiveAnimationId = 0;
}
