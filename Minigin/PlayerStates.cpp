#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "PlayerInputEvents.h"
#include <functional>
#include "StateComponent.h"
void dae::IdleState::EventNotify(StateArgs &  arg)
{
	DefaultState::EventNotify(arg);
	// Exit Condition
	if (arg.mFp_InputAction.second->EventType == EventTypes::LaunchHose)
	{
		m_StateComponent.NotifyonStateChange(new FlyingHoseState(m_StateComponent));
		return;
	}
	else 
	{
		auto vel = arg.mFp_InputAction.second->MComp.get().GetVelocity();
		if (vel != glm::vec2(0, 0))
			m_StateComponent.NotifyonStateChange(new WalkingState(m_StateComponent));
	}

		//if (arg)
}

void dae::WalkingState::EventNotify(StateArgs &  arg)
{
	 DefaultState::EventNotify(arg);

	 // Exit Condition
	 if (arg.mFp_InputAction.second->MComp.get().GetVelocity() == glm::vec2(0, 0) 
		 && ( arg.mFp_InputAction.second->DComp != nullptr && !arg.mFp_InputAction.second->DComp->HasDied() )
		 && arg.mFp_InputAction.second->EventType != EventTypes::StartPump)
		 m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
}

void dae::DefaultState::EventNotify(StateArgs &  arg)
{
	
	BaseState::EventNotify(arg);
	
	if (arg.mFp_InputAction.second->EventType == EventTypes::StartPump)
	{
		m_StateComponent.NotifyonStateChange(new PumpingState(m_StateComponent));
		return;
	}
	
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
	if (args.mFp_InputAction.second->EventType != EventTypes::Moving && args.mFp_InputAction.second->EventType != EventTypes::StartPump && args.mFp_InputAction.second->EventType != EventTypes::Dying)
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

void dae::RespawnState::EventNotify(StateArgs & args)
{
	if (args.mFp_InputAction.second->EventType != EventTypes::Moving && args.mFp_InputAction.second->EventType != EventTypes::StartPump && args.mFp_InputAction.second->EventType != EventTypes::Dying)
		BaseState::EventNotify(args);
}

void dae::RespawnState::Update(float )
{
	
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	
	
}

dae::GameOverState::GameOverState(StateComponent & stateComponent) : StaticState(stateComponent)
{
	m_StateComponent.m_EventGenComponent.GenerateGameOverEvent();
}

void dae::PumpingState::EventNotify(StateArgs & args)
{
	if (m_IsPumping ) 
	{  
		
		if (args.mFp_InputAction.second->EventType == EventTypes::PlayerPumping)
		{ 
			m_TimeUntillIdle = 60;
			m_TickCounter = 0;
		}
			BaseState::EventNotify(args);
	}
	else
	{
		if (args.mFp_InputAction.second->EventType == EventTypes::PlayerHitEnemy && !m_IsPumping)
		{
			m_IsPumping = true;
			m_TimeUntillIdle = 90;
			m_TickCounter = 0;
		}
		//if (args.mFp_InputAction.second->
		if (args.mFp_InputAction.second->EventType != EventTypes::Moving)
			BaseState::EventNotify(args);
	}
	
}

void dae::PumpingState::Update(float )
{
	m_TickCounter = m_TickCounter + 1 ;
	if (m_TickCounter >= m_TimeUntillIdle)
	{
		m_StateComponent.m_EventGenComponent.GeneratePumpEndEvent();
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	}
}

dae::FlyingHoseState::FlyingHoseState(StateComponent & stateComponent) : BaseState(stateComponent)
{

}

void dae::FlyingHoseState::EventNotify(StateArgs & args)
{
	if (args.mFp_InputAction.second->EventType == EventTypes::HoseHit ||
		 args.mFp_InputAction.second->EventType == EventTypes::HoseEnd || 
		args.mFp_InputAction.second->EventType == EventTypes::LaunchHose
		)
		BaseState::EventNotify(args);
}

void dae::FlyingHoseState::Update(float )
{
}

void dae::InflationState::EventNotify(StateArgs & args)
{
	if (args.mFp_InputAction.second->EventType == EventTypes::EnemyDeflated)
	{
		BaseState::EventNotify(args);
	
		m_StateComponent.NotifyonStateChange(new EnemyState(m_StateComponent));
		
	}
	if (args.mFp_InputAction.second->EventType == EventTypes::EnemyDeath)
	{
		m_HasDied = true; 
		BaseState::EventNotify(args);
		m_StateComponent.NotifyonStateChange(new EnemyDeathState(m_StateComponent));
	}
	if (!m_HasDied && (args.mFp_InputAction.second->EventType == EventTypes::EnemyPumped || args.mFp_InputAction.second->EventType == EventTypes::EnemyDeflating))
		BaseState::EventNotify(args);


}
void dae::EnemyState::EventNotify(StateArgs & args )
{
	if (args.mFp_InputAction.second->EventType == EventTypes::EnemyHit)
	{
		BaseState::EventNotify(args);
		m_StateComponent.NotifyonStateChange(new InflationState(m_StateComponent));
		
	}
	
}


void dae::InflationState::Update(float )
{
	m_TickCounter += 1;
	if (m_TickCounter > m_TimeUntillDeflate)
	{
		m_TickCounter = 0; 
		m_StateComponent.m_EventGenComponent.GenerateEnemyDeflateEvent();
	}
}

void dae::EnemyDeathState::EventNotify(StateArgs & arg)
{
	BaseState::EventNotify(arg);
}

void dae::EnemyDeathState::Update(float )
{
	m_TickCounter += 1;
	if (m_TickCounter > m_TimeUntillDespawn)
	{
		m_TickCounter = 0;
		m_StateComponent.m_EventGenComponent.GenerateEnemyDespawnEvent();
	}
}
