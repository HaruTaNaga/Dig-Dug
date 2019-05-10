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
		StateComponent(CommandComponent & commandCmp) ;

		virtual ~StateComponent() {  };
		void NotifyonStateChange(BaseState * state);
		void Notify(Command c);
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;
		CommandComponent & m_CommandComponent;  
	private: 
		std::unique_ptr<BaseState> m_CurrentState; 

	protected: 
		virtual void Update(float);
	};
}