#include "MiniginPCH.h"
#include "AiComponent.h"
#include  "CommandFactory.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "AiStates.h"
dae::AiComponent::~AiComponent()
{
}

dae::AiComponent::AiComponent(StateComponent & stateComp, PositionComponent & posCmp, MoveComponent & movCmp, AnimationComponent & aniCmp)
	: m_PositionComponent(posCmp),
	m_MoveComponent(movCmp),
	m_AnimationComponent(aniCmp),
	m_StateComponent(stateComp)
{
	m_CurrentState.reset(new IdleAiState(*this));
};

void dae::AiComponent::Update(float dt)
{
	auto newstate = m_CurrentState->Update(dt);
	if (newstate.first) 
		m_CurrentState.reset(newstate.second);
}
