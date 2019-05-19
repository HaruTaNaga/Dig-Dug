#include "MiniginPCH.h"
#include "AiComponent.h"
#include  "CommandFactory.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "AiStates.h"
#include "FireBreathComponent.h"
dae::AiComponent::~AiComponent()
{
}

dae::AiComponent::AiComponent(AiTypes enemyType, StateComponent & stateComp, PositionComponent & posCmp, MoveComponent & movCmp, AnimationComponent & aniCmp, CollisionComponent & CComp)
	: m_PositionComponent(posCmp),
	m_MoveComponent(movCmp),
	m_AnimationComponent(aniCmp),
	m_StateComponent(stateComp), 
	m_CollisionComponent(CComp), 
	m_EnemyType(enemyType)
{
	m_CurrentState.reset(new IdleAiState(*this));
};

void dae::AiComponent::Update(float dt)
{
	auto newstate = m_CurrentState->Update(dt);
	if (newstate.first) 
		m_CurrentState.reset(newstate.second);
}
