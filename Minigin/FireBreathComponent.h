#pragma once
#include "BaseComponent.h"

namespace dae {
	class FireComponent; 
	class PositionComponent; 
	class FygarOrientationComponent; 

	class FireBreathComponent : public BaseComponent
	{
	public: 

		FireBreathComponent(FygarOrientationComponent & oriComp, FireComponent & fireComp, PositionComponent & posComp);
		~FireBreathComponent() {};
		void Update(float) override {};

		void BreathFire(); 
		void EndFire(); 
		FygarOrientationComponent & m_OrientationComponent;

		FireComponent & m_FireComponent; 
		PositionComponent & m_PositionComponent;
	};
}