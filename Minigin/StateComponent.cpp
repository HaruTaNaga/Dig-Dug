#include "MiniginPCH.h"
#include "StateComponent.h"

#include "Command.h"
dae::StateComponent::StateComponent(CommandComponent & eventGenCmp) :
	m_EventGenComponent(eventGenCmp) 
	
{
	m_CurrentState.reset(new IdleState(*this));
	
	auto a = 5; 
	a += 5;  
}

void dae::StateComponent::NotifyonStateChange(BaseState * state)
{
	//delete m_CurrentState.get(); 
	m_CurrentState.reset(state); 
}

void dae::StateComponent::NotifyonEvent(std::pair<std::function<void(EventArgs*)>, EventArgs*> pair_FpEvent_Args)
{
	
	StateArgs s(pair_FpEvent_Args);
//	m_CurrentState->EventNotify(s);
}

void dae::StateComponent::NotifyonEvent(Command c)
{
	m_CurrentState->EventNotify(c);
}


void dae::StateComponent::Update(float dt )
{
	m_CurrentState->Update(dt); 
}
