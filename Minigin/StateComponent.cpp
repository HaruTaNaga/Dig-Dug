#include "MiniginPCH.h"
#include "StateComponent.h"

dae::StateComponent::StateComponent() 
	
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
	m_CurrentState->EventNotify(s);
}

void dae::StateComponent::Update(float dt )
{
	m_CurrentState->Update(dt); 
}
