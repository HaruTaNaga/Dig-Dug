#pragma once
#include <XInput.h>

#include "SDL.h"

#include "InputManager.h"
#include <functional>
#include "CommandFactory.h"
#include "EventArg.h"
namespace dae {
	struct PlayerInputKeyEvents; 
	class BaseComponent; 
	class MoveComponent; 
	class StateComponent;
	class CommandComponent; 
	class InputComponent final : public BaseComponent
	{
	public:
	
		InputComponent( StateComponent & sc, CommandComponent & eventcomp, PlayerIdentifier PlayerId = PlayerIdentifier::PlayerOne)  ;
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

		StateComponent & m_StateComponent; 
		CommandComponent & m_CommandComponent;

		SDL_Event m_event;
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		SDL_Keycode m_LastKeyReleased;
		InputManager * m_InputManager; 

		PlayerIdentifier m_PlayerId; 
	};

}