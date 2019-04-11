#pragma once

#include "BaseComponent.h"
#include "PositionComponent.h"

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace dae {

	class PhysicsComponent; 
	class PositionComponent; 
	class MoveComponent final : public BaseComponent
	{
	public: 

		MoveComponent(std::shared_ptr <GameObject>  owner, PositionComponent & positionComponent, PhysicsComponent & physicsComponent) 
			: BaseComponent(owner), mPositionComponent(positionComponent), mPhysicsComponent(physicsComponent) {};
		~MoveComponent() = delete;

		 //void Receive(int msg, dae::CmpType Destination) override;
		 void Update(float deltaTime) override;
		// dae::CmpType GetType() override { return dae::CmpType::moveComp; }
		 void SetVelocity(float x, float y) { mVelocity.x = x; mVelocity.y = y; }
		 void SetVelocity(glm::vec2 & vel) { mVelocity = vel; }
		 const glm::vec2 & GetVelocity() { return mVelocity; }
		 void AllignSprite(bool isAlligned, float velocity, float & position); 
		 void CalculateVelocity(const float currPos, glm::vec2 & newvel, bool & IsAliigned, const float vel, const bool isY);
		 bool xAlligned = true;
		 bool yAlligned = true;
	private: 
		Orientation mOrientation; 
		MoveComponent(); 
		PositionComponent & mPositionComponent;
		PhysicsComponent & mPhysicsComponent; 
		glm::vec2 mVelocity = glm::vec2(0,0);
		int m_AllignmentTriggerCtr;  
	};

}