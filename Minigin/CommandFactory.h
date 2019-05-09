#pragma once
#include <functional>
#include "SDL.h"

namespace dae {
	class EventArgs; 
	
	class CommandFactory {
	public: 
		CommandFactory() {};
		~CommandFactory(); 
		std::function<void(EventArgs *)> ReturnEventLamdaKeyDown(SDL_Keycode type);
		std::function<void(EventArgs *)> ReturnEventLamdaUp(SDL_Keycode type);
		std::function<void(EventArgs *)> ReturnEmptyEventLamda();
		std::function<void(EventArgs *)> ReturnDeathEvent(); 
		std::function<void(EventArgs *)> ReturnRespawnEvent();
		std::function<void(EventArgs *)> ReturnGameOverEvent();
		std::function<void(EventArgs *)> ReturnPumpLaunchEvent();
		std::function<void(EventArgs *)> ReturnPumpEndEvent();
		std::function<void(EventArgs *)> ReturnHoseLaunchEvent();
		std::function<void(EventArgs *)> ReturnHoseEndEvent();
		std::function<void(EventArgs *)> ReturnHoseHitEvent();
		std::function<void(EventArgs *)> ReturnEnemyHitEvent();
		std::function<void(EventArgs* )> ReturnStartPumpingEnemyEvent();
		std::function<void(dae::EventArgs*)> ReturnPlayerPumpingEnemyEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyPumpedEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyDeflationEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyDeflatedEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyDeathEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyDespawnEvent();
		std::function<void(dae::EventArgs*)> ReturnEnemyCrushedEvent();
	};
}