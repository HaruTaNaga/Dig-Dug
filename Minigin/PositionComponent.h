#pragma once
#include "BaseComponent.h"
#include "Transform.h"
namespace dae {

class PositionComponent : BaseComponent
{
private:

	dae::Transform mTransform;
public: 


	PositionComponent(std::shared_ptr <GameObject> owner) : BaseComponent(owner) {}

	~PositionComponent() {};
	PositionComponent(const PositionComponent& other) = delete;
	PositionComponent(PositionComponent&& other) = delete;
	PositionComponent& operator=(const PositionComponent& other) = delete;
	PositionComponent& operator=(PositionComponent&& other) = delete;

	//void Receive(int msg, dae::CmpType Destination) override {};
	void Update(float deltaTime) override;
	//dae::CmpType GetType() override { return dae::CmpType::posComp; }

	const glm::vec3& GetPosition();
	//const mTransForm& GetTransForm()
	void SetPosition(const glm::vec3 & pos);
	void SetPosition(float x, float y, float z);
};

}