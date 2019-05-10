#pragma once
#include "PhysicsManager.h"
#include  "ComponentsH.h"

namespace dae {
	 
	
	class CollisionComponent : public  BaseComponent {
	public:  
		CollisionComponent(CollisionFlags flags, CommandComponent & eventGenComponent) ;
		virtual ~CollisionComponent() override {};
		CollisionFlags m_CollisionCategoryFlags;
		PhysicsManager * m_PhysicsManager = nullptr;
		CommandComponent & m_CommandComponent; 
		void Update(float deltaTime) override;
		void SetHitBoxSize(int size) { m_HitBoxSize = size; }
		bool CheckCollision(dae::Vec2 pos);
		bool m_CanCollide = true;
	private: 
		CollisionComponent()  = delete;
		int m_HitBoxSize = 32; 
	
	};
}