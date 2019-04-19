#pragma once
//#include  "GameObject.h"
//#include "ComponentsH.h"
//#include  <vector>

namespace  dae {
	class PositionComponent; 
	class GameObject; 

	//class CollisionComponent; 
	struct Box {
		float x; 
		float y; 
		int width; 
		int height; 
		Box(float xpos, float ypos, int w = g_blocksize, int h = g_blocksize) :
			x(xpos ), y(ypos ), width(w), height(h)
		{}
	};
	class PhysicsManager {
	public: 
		PhysicsManager() ; 
		~PhysicsManager() = default	; 
		void InitActiveComponents(); 
		CollisionFlags CheckPlayerCollision(dae::Vec2);

		bool CheckBoxesIntersect(Box a, Box b) { return (abs((a.x ) - b.x) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));}
	
		std::vector<std::pair<PositionComponent *,GameObject*>> m_Pair_PosComp_GameObj;

	//	std::vector<CollisionComponent *> m_Actors;

	};
}