#include "MiniginPCH.h"
#include "StateComponent.h"
#include "IObserver.h"
#include "Command.h"
dae::StateComponent::StateComponent(CommandComponent & commandCmp, GameObject & gameObject) :
	m_CommandComponent(commandCmp), 
	m_Owner(gameObject)
{
	m_CurrentState.reset(new IdleState(*this));
	
	auto a = 5; 
	a += 5;  
}

void dae::StateComponent::NotifyonStateChange(BaseState * state)
{
	m_CurrentState.reset(state); 
}



void dae::StateComponent::Notify(Command & c)
{
	m_CurrentState->Notify(c);
}
void dae::StateComponent::AddObserver(dae::IObserver * obs)
{
	m_Observers.push_back(std::unique_ptr<IObserver>(obs));
}
void dae::StateComponent::NotifyEvent(EventTypes ev)
{
	for (auto & obs : m_Observers)
		obs->Notify(ev); 
}


void dae::StateComponent::Update(float dt )
{
	m_CurrentState->Update(dt); 
}
