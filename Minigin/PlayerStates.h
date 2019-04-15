#pragma once
//#include "ComponentsH.h"
#include "BaseState.h"
#include "BaseEvent.h"
#include <functional>
namespace dae {
	class StateComponent; 
	class StateArgs {
	public:
		virtual ~StateArgs() = default;
		StateArgs() {} // = delete;
		//StateArgs(StateComponent & statecomp) : m_StateComponent(statecomp) {};


	};
	class BaseState
	{
	public:
		BaseState(StateComponent & sComponent) : m_StateComponent(sComponent) {}
		virtual ~BaseState() = default;
		virtual void Update(StateArgs &) {};
		StateComponent & m_StateComponent;
	};
	class StandardStateArg : public StateArgs
	{
	public: 
		StandardStateArg(std::pair<std::function<void(EventArgs*)>, EventArgs*> pair) : mFp_InputAction(pair) {};
		~StandardStateArg() = default;
		std::pair<std::function<void(EventArgs *)>, EventArgs*> mFp_InputAction;
		//void(*FuncPointer_InputAction)(EventArgs) = nullptr;  
	};
	class DefaultState : public  BaseState
	{
	public: 
		DefaultState(StateComponent & stateComponent) : BaseState(stateComponent) {}
		void Update(StateArgs & arg) 
		{
			StandardStateArg & sarg = dynamic_cast<StandardStateArg &>(arg);
			sarg.mFp_InputAction.first(sarg.mFp_InputAction.second);
		};
		~DefaultState() = default;

	};
	

	class IdleState final : public DefaultState
	{
	public:
		void Update(StateArgs & arg) { DefaultState::Update(arg); };
		~IdleState() = default;
	private:

	};

	class WalkingState final : public DefaultState
	{
	public:
		void Update(StateArgs & arg) { DefaultState::Update(arg); };
		~WalkingState() = default;
	private:

	};


	class ShootingState final : public DefaultState
	{
	public:
		void Update(StateArgs & arg) { DefaultState::Update(arg); };
		~ShootingState() = default;
	private:

	};

	class PumpingState final : public DefaultState
	{
	public:
		void Update(StateArgs & arg) { DefaultState::Update(arg); };
		~PumpingState() = default;
	private:

	};
	class StaticState : public  BaseState
	{
	public:
		void Update(StateArgs & )
		{

		};
		~StaticState() = default;

	};
	class ChrushingState final : public StaticState
	{
	public:
		void Update(StateArgs & arg) { StaticState::Update(arg); };
		~ChrushingState() = default;
	private:

	};

	class DyingState final : public StaticState
	{
	public:
		void Update(StateArgs  & arg) { StaticState::Update(arg); };
		~DyingState() = default;
	private:

	};

	class RespawnState final : public StaticState
	{
	public:
		void Update(StateArgs  & arg) { StaticState::Update(arg); };
		~RespawnState() = default;
	private:

	};

}