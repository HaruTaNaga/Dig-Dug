#pragma once
namespace dae {
	class MoveComponent;
	class EventArgs
	{
	public:
		class EventArgs(MoveComponent & mc) : MComp(mc) {}; 
		virtual ~EventArgs() = default;
		MoveComponent & MComp;
	};
	class EventArgKeyDown final : public EventArgs
	{
	public:
		~EventArgKeyDown() = default;
		EventArgKeyDown(MoveComponent & mc) : EventArgs(mc) {};
		
	};
	class Event
	{
	public: 
		virtual ~Event() = default;
		virtual void Execute(EventArgs & EvArg) = 0;
	};

	

}
