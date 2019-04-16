#pragma once

#include "BaseComponent.h"
#include "PositionComponent.h"

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
namespace dae {
	class EventGenComponent; 
	class PhysicsComponent; 
	class PositionComponent; 
	class MoveComponent final : public BaseComponent
	{
	public: 

		MoveComponent(PositionComponent & positionComponent, PhysicsComponent & physicsComponent) 
			:m_PositionComponent(positionComponent), m_PhysicsComponent(physicsComponent) {};
		~MoveComponent() = delete;


		 void Update(float deltaTime) override;
		
		 void SetVelocity(float x, float y) { mVelocity.x = x; mVelocity.y = y; }
		 void SetVelocity(glm::vec2 & vel) { mVelocity = vel; }
		 const glm::vec2 & GetVelocity() { return mVelocity; }
		 void AllignSprite(bool isAlligned, float velocity, float & position); 
		 void CalculateVelocity(const float currPos, glm::vec2 & newvel, bool & IsAliigned, const float vel, const bool isY);
		 bool xAlligned = true;
		 bool yAlligned = true;
		 PositionComponent & m_PositionComponent;
	private: 
		
		MoveComponent(); 
	
		PhysicsComponent & m_PhysicsComponent; 
		glm::vec2 mVelocity = glm::vec2(0,0);
		int m_AllignmentTriggerCtr;  
	};

}