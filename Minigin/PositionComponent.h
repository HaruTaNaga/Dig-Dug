#pragma once
#include "BaseComponent.h"
#include "Transform.h"
namespace dae {

class PositionComponent : public BaseComponent
{
private:

	dae::Transform m_Transform;
public: 
	PositionComponent() {}
	virtual ~PositionComponent() {};
	PositionComponent(const PositionComponent& other) = delete;
	PositionComponent(PositionComponent&& other) = delete;
	PositionComponent& operator=(const PositionComponent& other) = delete;
	PositionComponent& operator=(PositionComponent&& other) = delete;
	void Update(float deltaTime) override;
	const glm::vec3& GetPosition();
	void SetPosition(const glm::vec3 & pos);
	void SetPosition(float x, float y, float z);
};

}