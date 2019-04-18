#pragma once
#include "BaseComponent.h"

namespace dae {
	class CollisionComponent; 
	class PositionComponent; 
	class PhysicsComponent :
		public BaseComponent
	{
	public:
		PhysicsComponent(std::shared_ptr <GameObject> owner, CollisionComponent & cComp) : m_CollisionComponent(cComp), BaseComponent(owner) {}
		virtual ~PhysicsComponent();

		void Update(float deltaTime) override;
		//dae::CmpType GetType() override { return dae::CmpType::moveComp; }

		bool IsOutOfMapBounds(const float x, const float y); 
		bool IsColliding(dae::Vec2 pos);
		CollisionComponent & m_CollisionComponent; 

	};


}
