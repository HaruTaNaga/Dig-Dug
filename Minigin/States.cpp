#include "MiniginPCH.h"
#include "States.h"

#include <functional>
#include "StateComponent.h"

void dae::IdleState::EventNotify(Command &  c)
{
	DefaultState::EventNotify(c);
	// Exit Condition
	if (c.Args->commandType == CommandTypes::LaunchHose)
	{
		m_StateComponent.NotifyonStateChange(new FlyingHoseState(m_StateComponent));
		return;
	}
	else
	{
		if (c.Args->MComp->GetVelocity() != glm::vec2(0, 0))
			m_StateComponent.NotifyonStateChange(new WalkingState(m_StateComponent));
	}
}


void dae::WalkingState::EventNotify(Command &  c)
{
	DefaultState::EventNotify(c);

	// Exit Condition
	if (c.Args->MComp->GetVelocity() == glm::vec2(0, 0)
		&& (c.Args->DComp != nullptr && !c.Args->DComp->HasDied())
		&& c.Args->commandType != CommandTypes::StartPump)
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
}


void dae::DefaultState::EventNotify(Command &  c)
{
	BaseState::EventNotify(c);

	if (c.Args->commandType == CommandTypes::StartPump)
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
	if (c.Args->commandType != CommandTypes::Moving
		&& c.Args->commandType != CommandTypes::StartPump
		&& c.Args->commandType != CommandTypes::Dying)
		BaseState::EventNotify(c);
}

void dae::DyingState::Update(float )
{
	m_TickCounter++; 
	if (m_TickCounter >= m_TimeUntillRespawn)
	{
		if (m_StateComponent.m_CommandComponent.m_DeathComponent->m_HpComponent.IsGameOver())
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
	m_StateComponent.m_CommandComponent.Respawn(); 
}


void dae::RespawnState::EventNotify(Command &  c)
{
if (c.Args->commandType != CommandTypes::Moving
		&& c.Args->commandType != CommandTypes::StartPump
		&& c.Args->commandType != CommandTypes::Dying)
		BaseState::EventNotify(c);
}

void dae::RespawnState::Update(float )
{
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));

}

dae::GameOverState::GameOverState(StateComponent & stateComponent) : StaticState(stateComponent)
{
	m_StateComponent.m_CommandComponent.GameOver();
}

void dae::PumpingState::EventNotify(Command &  c)
{
	if (m_IsPumping )  {  	
		if (c.Args->commandType == CommandTypes::PlayerPumping) {
			m_TimeUntillIdle = 60;
			m_TickCounter = 0;
		}
		BaseState::EventNotify(c);
	}
	else {
		if (c.Args->commandType == CommandTypes::PlayerHitEnemy && !m_IsPumping) 	{
			m_IsPumping = true;
			m_TimeUntillIdle = 90;
			m_TickCounter = 0;
		}
		if (c.Args->commandType != CommandTypes::Moving && c.Args->commandType != CommandTypes::StartPump)
			BaseState::EventNotify(c);
	}
}

void dae::PumpingState::Update(float )
{
	m_TickCounter = m_TickCounter + 1 ;
	if (m_TickCounter >= m_TimeUntillIdle)
	{
		m_StateComponent.m_CommandComponent.PumpEnd();
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	}
}

dae::FlyingHoseState::FlyingHoseState(StateComponent & stateComponent) : BaseState(stateComponent)
{

}


void dae::FlyingHoseState::EventNotify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::HoseHit ||
		c.Args->commandType == CommandTypes::HoseEnd ||
		c.Args->commandType == CommandTypes::LaunchHose
		)
		BaseState::EventNotify(c);
}

void dae::FlyingHoseState::Update(float )
{
}

void dae::InflationState::EventNotify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::EnemyDeflated)
	{
		BaseState::EventNotify(c);
	
		m_StateComponent.NotifyonStateChange(new EnemyState(m_StateComponent));
		
	}
	if (c.Args->commandType == CommandTypes::EnemyDeath)
	{
		m_HasDied = true; 
		BaseState::EventNotify(c);
		m_StateComponent.NotifyonStateChange(new EnemyDeathState(m_StateComponent));
	}
	if (!m_HasDied && (c.Args->commandType == CommandTypes::EnemyPumped || c.Args->commandType == CommandTypes::EnemyDeflating))
		BaseState::EventNotify(c);
}


void dae::EnemyState::EventNotify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::EnemyHit )
	{
		BaseState::EventNotify(c);
		m_StateComponent.NotifyonStateChange(new InflationState(m_StateComponent));

	}
	if (c.Args->commandType == CommandTypes::EnemyCrushed)
	{
		BaseState::EventNotify(c);
		m_StateComponent.NotifyonStateChange(new EnemyDeathState(m_StateComponent));

	}
		
}


void dae::InflationState::Update(float )
{
	m_TickCounter += 1;
	if (m_TickCounter > m_TimeUntillDeflate)
	{
		m_TickCounter = 0; 
		m_StateComponent.m_CommandComponent.EnemyDeflate();
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
		m_StateComponent.m_CommandComponent.EnemyDespawn();
	}
}
