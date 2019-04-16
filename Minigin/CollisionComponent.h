#pragma once
#include "PhysicsManager.h"
#include  "ComponentsH.h"
namespace dae {
	 
	
	class CollisionComponent : public  BaseComponent {
	public:  
		CollisionComponent(PositionComponent & posC, OrientationComponent & oriC, bool isPlayer , bool IsRock , bool IsEnemy);
		~CollisionComponent();
		const bool m_IsPlayerCollisionFlag;
		const bool m_IsRockCollisionFlag;
		const bool m_IsEnemyCollisionFlag;
		PositionComponent & m_PositionComponent; 
		OrientationComponent & m_OrientationComponent; 
		PhysicsManager * m_PhysicsManager = nullptr;
		void Update(float deltaTime) override;
		void SetHitBoxSize(int size) { m_HitBoxSize = size; }
	private: 
		CollisionComponent()  = delete;
		int m_HitBoxSize = 32; 

	};
}