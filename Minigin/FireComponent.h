#pragma once
#include "BaseComponent.h"
namespace dae {
	class PositionComponent;
	class AnimationComponent; 

	class FireComponent : public BaseComponent
	{
	public: 

		FireComponent(PositionComponent & posComp , AnimationComponent & AniComp); 
		~FireComponent() {};
		void Update(float deltaTime) override; 

		void Fire(bool IsFlipped, dae::Vec2 Position);
		void EndFire(); 
		bool m_IsFlipped =  false;
		PositionComponent & m_PositionComponent; 
		AnimationComponent & m_AnimationComponent; 
		int m_TickCounter = 0;  

	};
}