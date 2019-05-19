#pragma once
#include "ComponentsH.h"
#include "ResourceManager.h"

namespace dae {

	class OrientationComponent :public BaseComponent
	{
	public:
		OrientationComponent(MoveComponent & movcomp) : m_MoveComponent(movcomp) {
			

		};
		virtual ~OrientationComponent();
		void Update(float deltaTime) override;
		Orientation GetOrientation() { return m_Orientation; }
		Orientation m_Orientation = dae::Right;
		MoveComponent & m_MoveComponent; 
		

	};
}


