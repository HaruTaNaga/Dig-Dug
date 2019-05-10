#pragma once
#include "ComponentsH.h"
#include "States.h"
namespace dae {
	//class BaseState; 
	//class InputComponent; 
	class Command;
	class StateComponent : public BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent(CommandComponent & eventGenCmp) ;

		virtual ~StateComponent() {  };
		void NotifyonStateChange(BaseState * state);
		void NotifyonEvent(Command c);
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;
		CommandComponent & m_EventGenComponent;  
	private: 
		std::unique_ptr<BaseState> m_CurrentState; 

	protected: 
		virtual void Update(float);
	};
}