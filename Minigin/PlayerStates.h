#pragma once
//#include "ComponentsH.h"
#include "BaseState.h"
#include "BaseEvent.h"
#include <functional>
namespace dae {
	class StateComponent; 
	/*
	class StateArgs {
	public:
		virtual ~StateArgs() = default;
		StateArgs() {} // = delete;
		//StateArgs(StateComponent & statecomp) : m_StateComponent(statecomp) {};


	};*/

	class StateArgs //: public StateArgs
	{
	public: 
		StateArgs(std::pair<std::function<void(EventArgs*)>, EventArgs*> pair) : mFp_InputAction(pair) {};
		~StateArgs() = default;
		std::pair<std::function<void(EventArgs *)>, EventArgs*> mFp_InputAction;
		//void(*FuncPointer_InputAction)(EventArgs) = nullptr;  
	};
	class BaseState
	{
	public:
		//BaseState() : m_StateComponent(StateComponent()) {}; 
		BaseState(StateComponent & sComponent);//: m_StateComponent(sComponent) {}
		virtual ~BaseState();
		virtual void EventNotify(StateArgs & arg)
		{
			arg.mFp_InputAction.first(arg.mFp_InputAction.second);
		};
		virtual void Update(float dt);
		

		StateComponent & m_StateComponent;
	};
	class DefaultState : public  BaseState
	{
	public: 
		DefaultState(StateComponent & stateComponent) : BaseState(stateComponent) {}

		void EventNotify(StateArgs & arg) override;
	
		~DefaultState() = default;

	};
	

	class IdleState final : public DefaultState
	{
	public:
		IdleState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

		void EventNotify(StateArgs & arg) override;
		~IdleState() = default;
	private:

	};

	class WalkingState final : public DefaultState
	{
	public:
		WalkingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

		void EventNotify(StateArgs & arg) override;
		~WalkingState() = default;
	private:

	};


	class ShootingState final : public DefaultState
	{
	public:

		~ShootingState() = default;
	private:

	};

	class PumpingState final : public DefaultState
	{
	public:

		~PumpingState() = default;
	private:

	};
	class StaticState : public  BaseState
	{
	public:

		~StaticState() = default;

	};
	class ChrushingState final : public StaticState
	{
	public:

		~ChrushingState() = default;
	private:

	};

	class DyingState final : public StaticState
	{
	public:
		
		~DyingState() = default;
	private:

	};

	class RespawnState final : public StaticState
	{
	public:
	
		~RespawnState() = default;
	private:

	};

}