#pragma once
namespace dae {
	class EventArgs
	{
	public:

		virtual ~EventArgs() = default;
	};
	class Event
	{
	public: 
		virtual ~Event() = default;
		virtual void Execute(EventArgs & EvArg) = 0;
	};

	

}
