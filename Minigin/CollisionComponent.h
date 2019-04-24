#pragma once
#include "PhysicsManager.h"
#include  "ComponentsH.h"

namespace dae {
	 
	
	class CollisionComponent : public  BaseComponent {
	public:  
		CollisionComponent(CollisionFlags flags, EventGenComponent & eventGenComponent) ;
		virtual ~CollisionComponent() override {};
		CollisionFlags m_CollisionCategoryFlags;
		PhysicsManager * m_PhysicsManager = nullptr;
		EventGenComponent & m_EventGenComponent; 
		void Update(float deltaTime) override;
		void NotifyOnHit();
		void SetHitBoxSize(int size) { m_HitBoxSize = size; }
		bool CheckCollision(dae::Vec2 pos);
		bool m_CanCollide = true;
	private: 
		CollisionComponent()  = delete;
		int m_HitBoxSize = 32; 
	
	};
}