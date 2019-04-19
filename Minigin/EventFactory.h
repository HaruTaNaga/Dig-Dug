#pragma once
#include <functional>
#include "SDL.h"

namespace dae {
	class EventArgs; 
	
	class EventFactory {
	public: 
		EventFactory() {};
		~EventFactory(); 
		std::function<void(EventArgs *)> ReturnEventLamdaKeyDown(SDL_Keycode type);
		std::function<void(EventArgs *)> ReturnEventLamdaUp(SDL_Keycode type);
		std::function<void(EventArgs *)> ReturnEmptyEventLamda();
		std::function<void(EventArgs *)> ReturnDeathEvent(); 
		std::function<void(EventArgs *)> ReturnRespawnEvent();
	};
}