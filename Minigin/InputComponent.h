#pragma once
#include <XInput.h>
//#include "BaseComponent.h"
//#include "MoveComponent.h"
//#include "StateComponent.h"
#include "SDL.h"

#include "InputManager.h"
#include <functional>
#include "EventFactory.h"
#include "EventArg.h"
namespace dae {
	struct PlayerInputKeyEvents; 
	//class EventArgKeyDown;
	class BaseComponent; 
	class MoveComponent; 
	class StateComponent;
	class EventFactory;  
	class InputComponent final : public BaseComponent
	{
	public:
	
		InputComponent( StateComponent & sc, EventGenComponent & eventcomp, PlayerIdentifier PlayerId = PlayerIdentifier::PlayerOne)  ;
		virtual ~InputComponent() {};
		void Update(float deltaTime) override;
		void NotifyKeyEvent();
		void KeyDown();
		void KeyUp();
		bool m_WasKeyDown, m_WasKeyUp;

		// std::pair< void*, EventArgKeyDown> mFp_InputAction; //Illegal http://www.parashift.com/c++-faq-lite/cant-cvt-memfnptr-to-voidptr.html
		std::pair<std::function<void(EventArgs *)>, EventArgs * > mFp_InputAction ;
	private:
		InputComponent();
		//MoveComponent & m_MoveComponent;
		StateComponent & m_StateComponent; 
		EventGenComponent & m_EventGenComponent;
		//bool m_WasKeyDown, m_WasKeyUp;
		SDL_Event m_event;
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		SDL_Keycode m_LastKeyReleased;
		InputManager * m_InputManager; 
	//	PlayerInputKeyEvents * m_Events; 
	//	EventArgs m_EventArg; 
		EventFactory * m_EventFactory; 
		PlayerIdentifier m_PlayerId; 
	};

}