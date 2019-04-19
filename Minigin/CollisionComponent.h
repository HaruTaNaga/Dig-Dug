#pragma once
#include "PhysicsManager.h"
#include  "ComponentsH.h"

namespace dae {
	 
	
	class CollisionComponent : public  BaseComponent {
	public:  
		CollisionComponent(CollisionFlags flags, EventGenComponent & eventGenComponent) ;
		~CollisionComponent();
		CollisionFlags m_CollisionCategoryFlags;
		PhysicsManager * m_PhysicsManager = nullptr;
		EventGenComponent & m_EventGenComponent; 
		void Update(float deltaTime) override;
		void SetHitBoxSize(int size) { m_HitBoxSize = size; }
		bool CheckCollision(dae::Vec2 pos);
	private: 
		CollisionComponent()  = delete;
		int m_HitBoxSize = 32; 

	};
}