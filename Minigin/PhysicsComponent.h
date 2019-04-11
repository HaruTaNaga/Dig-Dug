#pragma once
#include "BaseComponent.h"

namespace dae {
	class PhysicsComponent :
		public BaseComponent
	{
	public:
		PhysicsComponent(std::shared_ptr <GameObject> owner) : BaseComponent(owner) {}
		virtual ~PhysicsComponent();

		void Update(float deltaTime) override;
		//dae::CmpType GetType() override { return dae::CmpType::moveComp; }

		bool IsOutOfMapBounds(const float x, const float y); 



	};


}
