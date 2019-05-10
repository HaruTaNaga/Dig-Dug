#pragma once
#include "BaseComponent.h"
#include "States.h"
namespace dae {
	class CommandComponent;
	class  Command;
	class BaseState; 

	class StateComponent : public BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent(CommandComponent & commandCmp) ;

		~StateComponent() override {  };
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