#include "MiniginPCH.h"
#include "StateComponent.h"

dae::StateComponent::StateComponent(InputComponent & incomp) 
	: m_InputComponent(incomp), m_CurrentState(std::unique_ptr<BaseState>(new DefaultState(*this)))
{
}

void dae::StateComponent::Update(float )
{
	auto pair_Fp_Arg = m_InputComponent.mFp_InputAction; 
	StandardStateArg sarg(pair_Fp_Arg);
	m_CurrentState->Update(sarg); 
}
