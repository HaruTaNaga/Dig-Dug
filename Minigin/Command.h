#pragma once
#include <functional>
#include "BaseEvent.h"
namespace dae {
	class EventArgs; 
	class Command
	{
	public:
		Command(std::pair<std::function<void(EventArgs*)>, EventArgs*> pair) : Function(pair.first) { Args = pair.second; };
		~Command() = default;
		//std::pair<std::function<void(EventArgs *)>, EventArgs*> pair_Function_Args;
		EventArgs* Args; 
		std::function<void(EventArgs *)> Function; 
	};

}

