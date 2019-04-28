#pragma once
#include "ComponentsH.h"
#include "PlayerStates.h"
namespace dae {
	//class BaseState; 
	//class InputComponent; 
	class Command;
	class StateComponent : public BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent(EventGenComponent & eventGenCmp) ;
		virtual ~StateComponent() {  };
		void NotifyonStateChange(BaseState * state);
		void NotifyonEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > pair_FpEvent_Args);

		void NotifyonEvent(Command c);
	
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;
		EventGenComponent & m_EventGenComponent; 
		BaseState * GetCurrentState(); 
	private: 
		//InputComponent & m_InputComponent; 
		std::unique_ptr<BaseState> m_CurrentState; 

	protected: 
		virtual void Update(float);
	};
}