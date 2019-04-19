#pragma once
#include  "EventFactory.h"
#include "BaseEvent.h"
#include "BaseComponent.h"
#include  "GameObject.h"
#include "ComponentsH.h"
namespace dae {
	class StateComponent; 
	class MoveComponent; 
	class PositionComponent; 
	class AnimationComponent; 
	class DeathComponent; 
	class EventGenComponent : public BaseComponent
	{
	public: 
		EventGenComponent(GameObject & go);
		void GenerateEmptyEvent();
		void GenerateKeyDownEvent(SDL_Keycode k);
		void GenerateKeyUpEvent(SDL_Keycode type);
		void GenerateDeathEvent(); 
		void GenerateRespawnEvent();
		void NotifyStateEvent(); 
		EventFactory * m_EventFactory;
	
		GameObject  & m_Owner; 
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::fpsComp; }
		EventGenComponent(const EventGenComponent& other) = delete;
		EventGenComponent(EventGenComponent&& other) = delete;
		EventGenComponent& operator=(const EventGenComponent& other) = delete;
		EventGenComponent& operator=(EventGenComponent&& other) = delete;
		std::pair<std::function<void(EventArgs *)>, EventArgs * > m_FpPairEventArg;
		std::unique_ptr<EventArgs> m_EventArg;
		StateComponent * m_StateComponent; 
		MoveComponent * m_MoveComponent; 
		AnimationComponent * m_AnimationComponent; 
		DeathComponent * m_DeathComponent; 

		void InitComponents(); 
	};
}