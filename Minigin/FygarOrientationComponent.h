#pragma once
#include "BaseComponent.h"

#include "DataStructs.h"
namespace dae {
	class MoveComponent; 

	class FygarOrientationComponent :public BaseComponent
	{
	public:
		FygarOrientationComponent(MoveComponent & movcomp) : m_MoveComponent(movcomp) {


		};
		virtual ~FygarOrientationComponent() {};
		void Update(float deltaTime) override;
		FygarOrientation GetOrientation() { return m_Orientation; }
		//dae::CmpType GetType()  { return dae::CmpType::inputComp; }
		FygarOrientation m_Orientation = FygarOrientation::FygarRight;
		MoveComponent & m_MoveComponent;

		
	};
}