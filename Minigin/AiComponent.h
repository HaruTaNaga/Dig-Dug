#pragma once
#include "BaseComponent.h"

//#include "PositionComponent.h"
namespace dae {
	class PositionComponent; 
	class BaseAiState; 
	class MoveComponent;
	class AnimationComponent; 
	//class CommandFactory; 
	class BaseAiState; 
	class StateComponent; 
	class CollisionComponent;
	class FireBreathComponent; 

	class AiComponent : public BaseComponent
	{
	public: 
		AiComponent(AiTypes enemyType, StateComponent & sCmp,  PositionComponent & posCmp,MoveComponent & movCmp, AnimationComponent & aniCmp, CollisionComponent & CComp);
		 ~AiComponent() override; 
		 void Update(float dt) override; 
		 std::unique_ptr<BaseAiState> m_CurrentState;
		 
		 AiTypes m_EnemyType; 

		 PositionComponent & m_PositionComponent; 
		 MoveComponent & m_MoveComponent; 
		 AnimationComponent  & m_AnimationComponent; 
		 StateComponent & m_StateComponent; 
		 CollisionComponent & m_CollisionComponent; 
		 FireBreathComponent * m_FireBreathComponent; 

		// CommandFactory * m_CommandFactory; 

	};
}