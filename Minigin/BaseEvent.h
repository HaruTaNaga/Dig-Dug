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
	class StateComponent; 
	class EventArgs
	{
	public:
		class EventArgs(MoveComponent & mc) : MComp(mc) {}; 
		virtual ~EventArgs() = default;
		union {

			std::reference_wrapper<MoveComponent> MComp;
			std::reference_wrapper<PositionComponent> PComp;
		};
		union {
			std::reference_wrapper<HoseComponent> HoseComp;
			std::reference_wrapper<PumpComponent> PumpComp;
			std::reference_wrapper<StateComponent> StateComp; 

		};
		DeathComponent * DComp; 
		AnimationComponent * AComp;
		EventTypes EventType; 
	};
	

}
