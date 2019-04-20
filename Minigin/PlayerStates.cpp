#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "PlayerInputEvents.h"
#include <functional>
#include "StateComponent.h"
void dae::IdleState::EventNotify(StateArgs &  arg)
{
	DefaultState::EventNotify(arg);
	// Exit Condition
	auto vel = arg.mFp_InputAction.second->MComp.get().GetVelocity();
	if (vel != glm::vec2(0,0))
		m_StateComponent.NotifyonStateChange(new WalkingState(m_StateComponent));
		//if (arg)
}

void dae::WalkingState::EventNotify(StateArgs &  arg)
{
	 DefaultState::EventNotify(arg);

	 // Exit Condition
	 if (arg.mFp_InputAction.second->MComp.get().GetVelocity() == glm::vec2(0, 0) && arg.mFp_InputAction.second->DComp != nullptr && !arg.mFp_InputAction.second->DComp->HasDied())
		 m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
}

void dae::DefaultState::EventNotify(StateArgs &  arg)
{

	BaseState::EventNotify(arg);
	
	if (arg.mFp_InputAction.second->DComp != nullptr && arg.mFp_InputAction.second->DComp->HasDied())
	{
		m_StateComponent.NotifyonStateChange(new DyingState(m_StateComponent));
		return;
	}
		
}




dae::BaseState::BaseState(StateComponent & sComponent)
	: m_StateComponent(sComponent) {}

dae::BaseState::~BaseState()
{
}

void dae::BaseState::Update(float )
{

};

void dae::DyingState::EventNotify(StateArgs & args)
{
	if (args.mFp_InputAction.second->IsMovementEvent != true)
		BaseState::EventNotify(args);
}

void dae::DyingState::Update(float )
{
	m_TickCounter++; 
	if (m_TickCounter >= m_TimeUntillRespawn)
	{
		if (m_StateComponent.m_EventGenComponent.m_DeathComponent->m_HpComponent.IsGameOver())
		{
			m_StateComponent.NotifyonStateChange(new GameOverState(m_StateComponent));
		}
		else
		{
		m_StateComponent.NotifyonStateChange(new RespawnState(m_StateComponent));
		}
		
	}
	
}

dae::RespawnState::RespawnState(StateComponent & stateComponent) : StaticState(stateComponent) 
{

	m_StateComponent.m_EventGenComponent.GenerateRespawnEvent(); 
	
	
}

void dae::RespawnState::Update(float )
{
	
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	
	
}

dae::GameOverState::GameOverState(StateComponent & stateComponent) : StaticState(stateComponent)
{
	m_StateComponent.m_EventGenComponent.GenerateGameOverEvent();
}
