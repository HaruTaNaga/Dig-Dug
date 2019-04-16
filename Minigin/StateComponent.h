#pragma once
#include "ComponentsH.h"
#include "PlayerStates.h"
namespace dae {
	//class BaseState; 
	//class InputComponent; 
	class StateComponent : BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent() ;
		virtual ~StateComponent() { delete m_CurrentState.get(); };
		void NotifyonStateChange(BaseState * state);
		void NotifyonEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > pair_FpEvent_Args);
	private: 
		//InputComponent & m_InputComponent; 
		std::unique_ptr<BaseState> m_CurrentState; 
	protected: 
		virtual void Update(float);
	};
}