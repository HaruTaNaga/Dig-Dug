#pragma once
class StateArgs {
	virtual ~StateArgs() = default; 
};
class BaseState
{
	public:
		
		virtual ~BaseState() = default;
		virtual void Update(StateArgs & EvArg) = 0;
};