#pragma once
#include "ComponentsH.h"

namespace dae {

	class FallComponent : public BaseComponent
	{
	public: 
		FallComponent(PositionComponent & posCmp, MoveComponent & MovComp, CollisionComponent & ColCmp);
		virtual ~FallComponent(); 
		void Update(float deltatime) override;
		
		PositionComponent & m_PositionComponent; 
		MoveComponent & m_MoveComponent; 
		CollisionComponent & m_CollisonComponent; 
		PhysicsManager * m_PhysicsManager; 
		MapManager * m_MapManager; 
		bool m_StartFalling; 
		bool m_IsFalling; 
		bool m_HasFallen; 
		int m_FallDelay = 0; 

	};
}