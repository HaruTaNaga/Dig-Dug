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
	class AiComponent : public BaseComponent
	{
	public: 
		AiComponent(StateComponent & sCmp,  PositionComponent & posCmp,MoveComponent & movCmp, AnimationComponent & aniCmp);
		 ~AiComponent() override; 
		 void Update(float dt) override; 
		 std::unique_ptr<BaseAiState> m_CurrentState;

		 PositionComponent & m_PositionComponent; 
		 MoveComponent & m_MoveComponent; 
		 AnimationComponent  & m_AnimationComponent; 
		 StateComponent & m_StateComponent; 
		// CommandFactory * m_CommandFactory; 

	};
}