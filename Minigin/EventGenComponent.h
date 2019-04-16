#pragma once
#include  "EventFactory.h"
#include "BaseEvent.h"
#include "BaseComponent.h"
#include  "GameObject.h"
namespace dae {

	class EventGenComponent :  BaseComponent
	{
	public: 
		EventGenComponent(GameObject & go);
		void GenerateEmptyEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > & p);
		void GenerateKeyDownEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > & p, SDL_Keycode k);
		void GenerateKeyUpEvent(std::pair<std::function<void(EventArgs *)>, EventArgs * > & p);
		EventFactory * m_EventFactory;
		std::unique_ptr<EventArgs> m_EventArg;
		GameObject  & m_Owner; 
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::fpsComp; }
		EventGenComponent(const EventGenComponent& other) = delete;
		EventGenComponent(EventGenComponent&& other) = delete;
		EventGenComponent& operator=(const EventGenComponent& other) = delete;
		EventGenComponent& operator=(EventGenComponent&& other) = delete;
	};
}