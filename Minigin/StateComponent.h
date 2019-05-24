#pragma once
#include "BaseComponent.h"
#include "States.h"
namespace dae {
	class CommandComponent;
	class  Command;
	class BaseState; 
	class IObserver; 
	class GameObject; 

	class StateComponent : public BaseComponent
	{
	public: 
		//StateComponent() = delete; 
		StateComponent(CommandComponent & commandCmp, GameObject & m_Owner) ;

		~StateComponent() override {  };
		void NotifyonStateChange(BaseState * state);
		void Notify(Command & c);
		void AddObserver(dae::IObserver * e);
		void NotifyEvent(EventTypes e);
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;
		CommandComponent & m_CommandComponent;  
		GameObject & m_Owner; 

		BaseState * GetState() { return m_CurrentState.get(); }
	private: 
		std::unique_ptr<BaseState> m_CurrentState; 
		std::vector<std::unique_ptr<IObserver>> m_Observers;
	protected: 
		virtual void Update(float);
	};
}