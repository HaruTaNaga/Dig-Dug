#pragma once
#include <functional>

namespace dae {
	class MoveComponent;
	class PositionComponent; 
	class AnimationComponent; 
	class DeathComponent; 
	class HoseComponent; 
	class PumpComponent; 
	class OrientationComponent; 
	class EventArgs
	{
	public:
		//class EventArgs() {};
		class EventArgs(MoveComponent & mc) : MComp(mc) {}; 
		virtual ~EventArgs() = default;
		union {

			std::reference_wrapper<MoveComponent> MComp;
			std::reference_wrapper<PositionComponent> PComp;
		};
		union {
			std::reference_wrapper<HoseComponent> HoseComp;
			std::reference_wrapper<PumpComponent> PumpComp;
		};
		DeathComponent * DComp; 
		AnimationComponent * AComp;
	//	PositionComponent * PosComp;
	//	OrientationComponent * OriCmp; 
		EventTypes EventType; 
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
