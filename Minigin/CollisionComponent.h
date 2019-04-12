#pragma once

#include  "ComponentsH.h"
namespace dae {
	 
	class CollisionComponent : public  BaseComponent {
	public:  
		CollisionComponent(std::shared_ptr<GameObject> owner, PositionComponent & posC, bool isPlayer , bool IsRock , bool Isenemy);
		~CollisionComponent();
		const bool m_IsPlayerCollisionFlag;
		const bool m_IsRockCollisionFlag;
		const bool m_IsEnemyCollisionFlag;
		PositionComponent & m_PositionComponent; 

	private: 
		CollisionComponent()  = delete;


	};
}