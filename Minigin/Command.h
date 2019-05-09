#pragma once
#include <functional>
#include "cArgs.h"
namespace dae {
	class cArgs; 
	class Command
	{
	public:
		Command(std::pair<std::function<void(cArgs*)>, cArgs*> pair) : Function(pair.first) { Args = pair.second; };
		~Command() = default;

		cArgs* Args; 
		std::function<void(cArgs *)> Function; 
	};

}

