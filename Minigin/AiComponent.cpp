#include "MiniginPCH.h"
#include "AiComponent.h"
#include  "CommandFactory.h"
#include "MoveComponent.h"
#include "AnimationComponent.h"
#include "AiStates.h"
#include "FireBreathComponent.h"
#include <future>
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

	if (firstFrame)
	{
		firstFrame = false; 
		result = std::future < std::pair<bool, BaseAiState *>>(std::async(&BaseAiState::Update, m_CurrentState.get(), dt));

		return;
	}
		auto newstate = result.get();
		if (newstate.first)
			m_CurrentState.reset(newstate.second);
		result = std::future < std::pair<bool, BaseAiState *>>(std::async(&BaseAiState::Update, m_CurrentState.get(), dt));

	
}
