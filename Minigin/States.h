#pragma once
//#include "ComponentsH.h"

#include "cArgs.h"
#include  "Command.h"
#include <functional>
namespace dae {
	class StateComponent; 
	class Command;


	class StateArgs
	{
	public: 
		StateArgs(std::pair<std::function<void(cArgs*)>, cArgs*> pair) : mFp_InputAction(pair) {};
		~StateArgs() = default;
		std::pair<std::function<void(cArgs *)>, cArgs*> mFp_InputAction;
	};
	class BaseState
	{
	public:
	
		BaseState(StateComponent & sComponent);
		virtual ~BaseState();
		
		virtual void EventNotify(Command &  c) 
		{
			c.Function(c.Args);
		};
		virtual void Update(float dt);
		

		StateComponent & m_StateComponent;
	};
	class DefaultState : public  BaseState
	{
	public: 
		DefaultState(StateComponent & stateComponent) : BaseState(stateComponent) {}

		
		void EventNotify(Command &  c) override;
		~DefaultState() = default;

	};
	

	class IdleState final : public DefaultState
	{
	public:
		IdleState() = delete; 
		IdleState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

	
		void EventNotify(Command &  c) override;
		~IdleState() = default;

	private:

	};

	class WalkingState final : public DefaultState
	{
	public:
		WalkingState() = delete; 
		WalkingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}

	
		void EventNotify(Command &  c) override;
		~WalkingState() = default;
	private:

	};


	class PumpingState final : public DefaultState
	{
	public:
		PumpingState() = delete; 
		PumpingState(StateComponent & stateComponent) : DefaultState(stateComponent) {}
		~PumpingState() = default;
		
		void EventNotify(Command &  c) override;
		void Update(float dt) override;
		void ResetTickCounter() 
		{
			m_TickCounter = 0; 
		}
		int m_TickCounter = 0;
		int m_TimeUntillIdle = 30 * 2;
		bool m_IsPumping = false; 

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
		
		void EventNotify(Command &  c) override;
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
	
		void EventNotify(Command &  c) override;
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
	
		void EventNotify(Command &  c) override;
		void Update(float dt) override;
	};
	class EnemyState : public BaseState
	{
	public: 
		EnemyState() = delete;
		EnemyState(StateComponent & stateComponent) : BaseState(stateComponent) {};
		~EnemyState() = default;
	
		void EventNotify(Command &  c) override;
	};
	class InflationState : public  BaseState
	{
	public:
		InflationState() = delete;
		InflationState(StateComponent & stateComponent) : BaseState(stateComponent) {};
		~InflationState() = default;
	
		void EventNotify(Command &  c) override;
		void Update(float dt) override;

		bool m_HasDied = false; 
		int m_TickCounter = 0; 
		int m_TimeUntillDeflate = 60; 

	};
	class EnemyDeathState : public  BaseState
	{
	public:
		EnemyDeathState() = delete;
		EnemyDeathState(StateComponent & stateComponent) : BaseState(stateComponent) {};
		~EnemyDeathState() = default;

		void EventNotify( Command &  c) override;
		void Update(float dt) override;


		int m_TickCounter = 0;
		int m_TimeUntillDespawn = 30;

	};
}