#pragma once
#include "ComponentsH.h"
#include "PlayerStates.h"
namespace dae {
	//class BaseState; 
	//class InputComponent; 
	class StateComponent : public BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent() ;
		virtual ~StateComponent() {  };
		void NotifyonStateChange(BaseState * state);
		void NotifyonEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > pair_FpEvent_Args);
	
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;
	private: 
		//InputComponent & m_InputComponent; 
		std::unique_ptr<BaseState> m_CurrentState; 

	protected: 
		virtual void Update(float);
	};
}