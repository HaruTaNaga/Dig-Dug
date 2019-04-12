#pragma once

#include "GameObject.h"
#include  <vector>
namespace  dae {


	class PhysicsManager {

		PhysicsManager() = default; 
		~PhysicsManager() = default	; 
	
			

		std::vector<GameObject &> m_Actors;

	};
}