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
		//DefaultState() = delete; 
		DefaultState(StateComponent & stateComponent) : BaseState(stateComponent) {}

		virtual void EventNotify(StateArgs & arg) override;
		//virtual void Update(float) override; 
		~DefaultState() = default;

	};
	

	class IdleState final : public DefaultState
	{
	public:
		IdleState() = delete; 
		IdleState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

		void EventNotify(StateArgs & arg) override;
		~IdleState() = default;
		//virtual void EventNotify(StateArgs & arg) override;
	private:

	};

	class WalkingState final : public DefaultState
	{
	public:
		WalkingState() = delete; 
		WalkingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

		void EventNotify(StateArgs & arg) override;
		~WalkingState() = default;
	private:

	};

	/*
	class ShootingState final : public DefaultState
	{
	public:
		ShootingState() = delete; 
		ShootingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}
		~ShootingState() = default;
	private:

	};*/

	class PumpingState final : public DefaultState
	{
	public:
		PumpingState() = delete; 
		PumpingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}
		~PumpingState() = default;
		void EventNotify(StateArgs &) override;
		void Update(float dt) override;
	private:
		int m_TickCounter = 0;
		int m_TimeUntillIdle = 30 * 2;

	};
	class StaticState : public  BaseState
	{
	public:
		StaticState() = delete;
		StaticState(StateComponent & stateComponent) : BaseState(stateComponent) {}
		~StaticState() = default;

	};
	class ChrushingState final : public StaticState
	{
	public:
		ChrushingState() = delete;
		ChrushingState(StateComponent & stateComponent) : StaticState(stateComponent) {}
		~ChrushingState() = default;
	private:

	};

	class DyingState final : public StaticState
	{
	public:
		DyingState() = delete; 
		DyingState(StateComponent & stateComponent) : StaticState(stateComponent) { m_TickCounter = 0; }
		~DyingState() = default;
		void EventNotify(StateArgs & ) override;
		void Update(float dt) override;
	private:
		int m_TickCounter = 0;
		int m_TimeUntillRespawn = 30 * 5; 
	};
 
	class RespawnState final : public StaticState
	{

	public:
		RespawnState() = delete;
		RespawnState(StateComponent & stateComponent);
		~RespawnState() = default;
		void EventNotify(StateArgs & ) override;
		void Update(float dt) override;
	private:

	};
	class GameOverState final : public StaticState
	{

	public:
		GameOverState() = delete;
		GameOverState(StateComponent & stateComponent);
		~GameOverState() = default;
	//	void EventNotify(StateArgs &) override {};
		void Update(float ) override {};
	private:

	};

	class FlyingHoseState : public  BaseState
	{
	public: 
		FlyingHoseState() = delete;
		FlyingHoseState(StateComponent & stateComponent);
		~FlyingHoseState() = default;
		void EventNotify(StateArgs &) override;
		void Update(float dt) override;
	};

}