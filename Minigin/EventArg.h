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
		//EventArgs() {}; 
		EventArgs() = default;
		union {

			MoveComponent * MComp;
			PositionComponent * PComp;
		};
		union {
			HoseComponent * HoseComp;
			PumpComponent * PumpComp;
			StateComponent * StateComp; 

		};
		DeathComponent * DComp; 
		AnimationComponent * AComp;
		EventTypes EventType; 
	};
	

}
