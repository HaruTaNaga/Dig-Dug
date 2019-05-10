#pragma once
#include <XInput.h>

#include "SDL.h"

#include "InputManager.h"
#include <functional>
#include "CommandFactory.h"
#include "cArgs.h"
namespace dae {
	struct PlayerInputKeyEvents; 
	class BaseComponent; 
	class MoveComponent; 
	class StateComponent;
	class CommandComponent; 
	class InputComponent final : public BaseComponent
	{
	public:
	
		InputComponent( StateComponent & sc, CommandComponent & eventcomp, PlayerTypes PlayerId = PlayerTypes::PlayerOne)  ;
		virtual ~InputComponent() {};
		void Update(float deltaTime) override;
		
		void KeyDown();
		void KeyUp();
		bool m_WasKeyDown, m_WasKeyUp;

		
		std::pair<std::function<void(cArgs *)>, cArgs * > mFp_InputAction ;
	private:
		InputComponent();

		StateComponent & m_StateComponent; 
		CommandComponent & m_CommandComponent;

		
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		SDL_Keycode m_LastKeyReleased;
		InputManager * m_InputManager; 

		PlayerTypes m_PlayerId; 
	};

}