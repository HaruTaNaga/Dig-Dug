#pragma once
#include "ComponentsH.h"
#include "PlayerStates.h"
namespace dae {
	//class BaseState; 
	class InputComponent; 
	class StateComponent : BaseComponent
	{
	public: 
		StateComponent() = delete; 
		StateComponent(InputComponent & incomp) ;
		virtual ~StateComponent() {};
	private: 
		InputComponent & m_InputComponent; 
		std::unique_ptr<BaseState> m_CurrentState; 
	protected: 
		virtual void Update(float);
	};
}