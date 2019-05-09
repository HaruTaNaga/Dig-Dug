#pragma once
#include <functional>
#include "SDL.h"

namespace dae {
	class cArgs; 
	
	class CommandFactory {
	public: 
		CommandFactory() {};
		~CommandFactory(); 
		std::function<void(cArgs *)> ReturnEventLamdaKeyDown(SDL_Keycode type);
		std::function<void(cArgs *)> ReturnEventLamdaUp(SDL_Keycode type);
		std::function<void(cArgs *)> ReturnEmptyEventLamda();
		std::function<void(cArgs *)> ReturnDeathEvent(); 
		std::function<void(cArgs *)> ReturnRespawnEvent();
		std::function<void(cArgs *)> ReturnGameOverEvent();
		std::function<void(cArgs *)> ReturnPumpLaunchEvent();
		std::function<void(cArgs *)> ReturnPumpEndEvent();
		std::function<void(cArgs *)> ReturnHoseLaunchEvent();
		std::function<void(cArgs *)> ReturnHoseEndEvent();
		std::function<void(cArgs *)> ReturnHoseHitEvent();
		std::function<void(cArgs *)> ReturnEnemyHitEvent();
		std::function<void(cArgs* )> ReturnStartPumpingEnemyEvent();
		std::function<void(cArgs*)> ReturnPlayerPumpingEnemyEvent();
		std::function<void(cArgs*)> ReturnEnemyPumpedEvent();
		std::function<void(cArgs*)> ReturnEnemyDeflationEvent();
		std::function<void(cArgs*)> ReturnEnemyDeflatedEvent();
		std::function<void(cArgs*)> ReturnEnemyDeathEvent();
		std::function<void(cArgs*)> ReturnEnemyDespawnEvent();
		std::function<void(cArgs*)> ReturnEnemyCrushedEvent();
	};
}