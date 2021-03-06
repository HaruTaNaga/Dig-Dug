#include "MiniginPCH.h"
#include "States.h"

#include <functional>
#include "StateComponent.h"

void dae::IdleState::Notify(Command &  c)
{

	// Exit Condition
	if (c.Args->commandType == CommandTypes::LaunchHose)
	{
		DefaultState::Notify(c);
		m_StateComponent.NotifyonStateChange(new FlyingHoseState(m_StateComponent));
		return;
	}
	else
	{
		if (c.Args->MComp != nullptr && c.Args->MComp->GetVelocity() != glm::vec2(0, 0))
		{
			m_StateComponent.NotifyonStateChange(new WalkingState(m_StateComponent));
			return;
		}
		
	}
	DefaultState::Notify(c);
}


void dae::WalkingState::Notify(Command &  c)
{
	// Exit Condition
	/*if (c.Args->commandType == CommandTypes::StartPump)
	{
		DefaultState::Notify(c);
		m_StateComponent.NotifyonStateChange(new PumpingState(m_StateComponent));
		return;
	}*/
	if (c.Args->MComp->GetVelocity() == glm::vec2(0, 0)
		&& (c.Args->DComp != nullptr && !c.Args->DComp->HasDied())
		&& c.Args->commandType != CommandTypes::StartPump)
	{
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
		return;
	}
		

	DefaultState::Notify(c);

	
}


void dae::DefaultState::Notify(Command &  c)
{
	if (c.Args->DComp != nullptr && c.Args->DComp->HasDied())
	{
		m_StateComponent.NotifyonStateChange(new DyingState(m_StateComponent));
		return;
	}


	if (c.Args->commandType == CommandTypes::StartPump)
	{
		BaseState::Notify(c);
		m_StateComponent.NotifyonStateChange(new PumpingState(m_StateComponent));
	
		return;
	}

	BaseState::Notify(c);
}




dae::BaseState::BaseState(StateComponent & sComponent)
	: m_StateComponent(sComponent) {}

dae::BaseState::~BaseState()
{
	
}

void dae::BaseState::Update(float )
{

};

void dae::DyingState::Notify(Command &  c)
{
	if (c.Args->commandType != CommandTypes::Moving
		&& c.Args->commandType != CommandTypes::StartPump
		&& c.Args->commandType != CommandTypes::Dying)
		BaseState::Notify(c);
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


void dae::RespawnState::Notify(Command &  c)
{
if (c.Args->commandType != CommandTypes::Moving
		&& c.Args->commandType != CommandTypes::StartPump
		&& c.Args->commandType != CommandTypes::Dying)
		BaseState::Notify(c);
}

void dae::RespawnState::Update(float )
{
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));

}

dae::GameOverState::GameOverState(StateComponent & stateComponent) : StaticState(stateComponent)
{
	m_StateComponent.m_CommandComponent.GameOver();
}

void dae::PumpingState::Notify(Command &  c)
{
	if (m_IsPumping )  {  	
		if (c.Args->commandType == CommandTypes::PlayerPumping) {
			m_TimeUntillIdle = 60;
			m_TickCounter = 0;
		}
		BaseState::Notify(c);
	}
	else {
		if (c.Args->commandType == CommandTypes::PlayerHitEnemy && !m_IsPumping) 	{
			m_IsPumping = true;
			m_TimeUntillIdle = 90;
			m_TickCounter = 0;
		}
		if (c.Args->commandType != CommandTypes::Moving && c.Args->commandType != CommandTypes::StartPump)
			BaseState::Notify(c);
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


void dae::FlyingHoseState::Notify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::HoseHit ||
		c.Args->commandType == CommandTypes::HoseEnd ||
		c.Args->commandType == CommandTypes::LaunchHose
		)
		BaseState::Notify(c);
}

void dae::FlyingHoseState::Update(float )
{
}

void dae::InflationState::Notify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::EnemyDeflated)
	{
		BaseState::Notify(c);
	
		m_StateComponent.NotifyonStateChange(new EnemyState(m_StateComponent));
		
	}
	if (c.Args->commandType == CommandTypes::EnemyDeath)
	{
		m_HasDied = true; 
		BaseState::Notify(c);
		m_StateComponent.NotifyonStateChange(new EnemyDeathState(m_StateComponent));
	}
	if (!m_HasDied && (c.Args->commandType == CommandTypes::EnemyPumped || c.Args->commandType == CommandTypes::EnemyDeflating))
	{
		m_TickCounter = 0;
		BaseState::Notify(c);
	}
		
}


void dae::EnemyState::Notify(Command &  c)
{
	if (c.Args->commandType == CommandTypes::EnemyHit )
	{
		BaseState::Notify(c);
		m_StateComponent.NotifyonStateChange(new InflationState(m_StateComponent));

	}
	if (c.Args->commandType == CommandTypes::EnemyCrushed)
	{
		m_StateComponent.NotifyEvent(EventTypes::EnemyDied);
		BaseState::Notify(c);
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



void dae::EnemyDeathState::Notify(Command &  c  )
{
	if (c.Args->commandType == CommandTypes::EnemyDespawn)
	BaseState::Notify(c);
}

void dae::EnemyDeathState::Update(float )
{
	m_TickCounter += 1;
	if (m_TickCounter > m_TimeUntillDespawn)
	{
		auto ypos = m_StateComponent.m_CommandComponent.m_PositionComponent->GetPosition().y;
		ypos = ypos - (32 * g_empty_top_rows);
		int layer = (int)fmod(ypos , 32) / 4;
		int scoreMod = 1;
		if (m_StateComponent.m_CommandComponent.m_Owner.GetComponent < FireBreathComponent>() != nullptr)
			scoreMod = 2;
		auto score = (200 + (100 * (1 + layer))) * scoreMod;
		ServiceLocator::GetScoreManager()->AddScore(score);

		m_StateComponent.NotifyEvent(EventTypes::EnemyDied);
		m_TickCounter = 0;
		m_StateComponent.m_CommandComponent.EnemyDespawn();
		m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
	}
}
