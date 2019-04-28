#include "MiniginPCH.h"
#include "PlayerStates.h"

#include <functional>
#include "StateComponent.h"

void dae::IdleState::EventNotify(Command &  c)
{
	DefaultState::EventNotify(c);
	// Exit Condition
	if (c.Args->EventType == EventTypes::LaunchHose)
	{
		m_StateComponent.NotifyonStateChange(new FlyingHoseState(m_StateComponent));
		return;
	}
	else
	{
		if (c.Args->MComp.get().GetVelocity() != glm::vec2(0, 0))
			m_StateComponent.NotifyonStateChange(new WalkingState(m_StateComponent));
	}


}


void dae::WalkingState::EventNotify(Command &  c)
{
	DefaultState::EventNotify(c);

	// Exit Condition
	if (c.Args->MComp.get().GetVelocity() == glm::vec2(0, 0)
		&& (c.Args->DComp != nullptr && !c.Args->DComp->HasDied())
		&& c.Args->EventType != EventTypes::StartPump)
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
}


void dae::DefaultState::EventNotify(Command &  c)
{
	BaseState::EventNotify(c);

	if (c.Args->EventType == EventTypes::StartPump)
	{
		m_StateComponent.NotifyonStateChange(new PumpingState(m_StateComponent));
		return;
	}

	if (c.Args->DComp != nullptr && c.Args->DComp->HasDied())
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

void dae::DyingState::EventNotify(Command &  c)
{
	if (c.Args->EventType != EventTypes::Moving
		&& c.Args->EventType != EventTypes::StartPump
		&& c.Args->EventType != EventTypes::Dying)
		BaseState::EventNotify(c);
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


void dae::RespawnState::EventNotify(Command &  c)
{
if (c.Args->EventType != EventTypes::Moving
		&& c.Args->EventType != EventTypes::StartPump
		&& c.Args->EventType != EventTypes::Dying)
		BaseState::EventNotify(c);
}

void dae::RespawnState::Update(float )
{
	
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	
	
}

dae::GameOverState::GameOverState(StateComponent & stateComponent) : StaticState(stateComponent)
{
	m_StateComponent.m_EventGenComponent.GenerateGameOverEvent();
}

void dae::PumpingState::EventNotify(Command &  c)
{
	if (m_IsPumping )  {  	
		if (c.Args->EventType == EventTypes::PlayerPumping) { 
			m_TimeUntillIdle = 60;
			m_TickCounter = 0;
		}
		BaseState::EventNotify(c);
	}
	else {
		if (c.Args->EventType == EventTypes::PlayerHitEnemy && !m_IsPumping) 	{
			m_IsPumping = true;
			m_TimeUntillIdle = 90;
			m_TickCounter = 0;
		}
		if (c.Args->EventType != EventTypes::Moving)
			BaseState::EventNotify(c);
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


void dae::FlyingHoseState::EventNotify(Command &  c)
{
	if (c.Args->EventType == EventTypes::HoseHit ||
		c.Args->EventType == EventTypes::HoseEnd || 
		c.Args->EventType == EventTypes::LaunchHose
		)
		BaseState::EventNotify(c);
}

void dae::FlyingHoseState::Update(float )
{
}

void dae::InflationState::EventNotify(Command &  c)
{
	if (c.Args->EventType == EventTypes::EnemyDeflated)
	{
		BaseState::EventNotify(c);
	
		m_StateComponent.NotifyonStateChange(new EnemyState(m_StateComponent));
		
	}
	if (c.Args->EventType == EventTypes::EnemyDeath)
	{
		m_HasDied = true; 
		BaseState::EventNotify(c);
		m_StateComponent.NotifyonStateChange(new EnemyDeathState(m_StateComponent));
	}
	if (!m_HasDied && (c.Args->EventType == EventTypes::EnemyPumped || c.Args->EventType == EventTypes::EnemyDeflating))
		BaseState::EventNotify(c);
}


void dae::EnemyState::EventNotify(Command &  c)
{
	if (c.Args->EventType == EventTypes::EnemyHit || c.Args->EventType == EventTypes::EnemyCrushed)
	{
		BaseState::EventNotify(c);
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



void dae::EnemyDeathState::EventNotify(Command &  c)
{
	BaseState::EventNotify(c);
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
