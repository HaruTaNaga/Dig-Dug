#pragma once
#include "ComponentsH.h"
#include "ResourceManager.h"

namespace dae {

	class OrientationComponent :public BaseComponent
	{
	public:
		OrientationComponent(MoveComponent & movcomp) : m_MoveComponent(movcomp) {
			

		};
		~OrientationComponent();
		void Update(float deltaTime) override;
		Orientation GetOrientation() { return m_Orientation; }
		//dae::CmpType GetType()  { return dae::CmpType::inputComp; }
		Orientation m_Orientation = dae::Right;
		MoveComponent & m_MoveComponent; 
		
		std::shared_ptr<Texture2D> m_Textures[4];
	};
}


