#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "PlayerInputEvents.h"
#include <functional>

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
	 if (arg.mFp_InputAction.second->MComp.get().GetVelocity() == glm::vec2(0, 0))
		 m_StateComponent.NotifyonStateChange(new IdleState(m_StateComponent));
}

void dae::DefaultState::EventNotify(StateArgs &  arg)
{

	BaseState::EventNotify(arg);
	
}

dae::BaseState::BaseState(StateComponent & sComponent)
	: m_StateComponent(sComponent) {}

dae::BaseState::~BaseState()
{
}

void dae::BaseState::Update(float dt)
{
	auto a = dt;
	a += 5;
};
