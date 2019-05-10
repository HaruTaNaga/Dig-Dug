#include "MiniginPCH.h"
#include "StateComponent.h"

#include "Command.h"
dae::StateComponent::StateComponent(CommandComponent & commandCmp) :
	m_CommandComponent(commandCmp)
{
	m_CurrentState.reset(new IdleState(*this));
	
	auto a = 5; 
	a += 5;  
}

void dae::StateComponent::NotifyonStateChange(BaseState * state)
{
	m_CurrentState.reset(state); 
}



void dae::StateComponent::Notify(Command c)
{
	m_CurrentState->Notify(c);
}


void dae::StateComponent::Update(float dt )
{
	m_CurrentState->Update(dt); 
}
