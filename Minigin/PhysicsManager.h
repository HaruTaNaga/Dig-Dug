#pragma once

#include "ComponentsH.h"
#include  <vector>
namespace  dae {

	class  CollisionComponent; 
	class PhysicsManager {

		PhysicsManager() = default; 
		~PhysicsManager() = default	; 
		

		std::vector<CollisionComponent *> m_Actors;

	};
}