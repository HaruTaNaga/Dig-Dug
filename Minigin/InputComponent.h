#pragma once
#include <XInput.h>
//#include "BaseComponent.h"
//#include "MoveComponent.h"
//#include "StateComponent.h"
#include "SDL.h"
#include "PlayerInputEvents.h"
#include "InputManager.h"
#include <functional>
namespace dae {
	struct PlayerInputKeyEvents; 
	class EventArgKeyDown;
	class BaseComponent; 
	class MoveComponent; 
	class StateComponent; 
	class InputComponent final : public BaseComponent
	{
	public:
		enum EventTypesEnum {
		Right,
		Left,
		Down,
		Up,
		KeyReleased,
		Empty
		};
		InputComponent(MoveComponent & mc, StateComponent & sc, std::shared_ptr<GameObject> owner)  ;
		~InputComponent() {};
		void Update(float deltaTime) override;
		void KeyDown();
		void KeyUp();
		bool m_WasKeyDown, m_WasKeyUp;
		std::function<void(EventArgs *)> ReturnEmptyEventLamda();
		
		//std::function<void(EventArgs *)> ReturnEventLamda(EventTypesEnum type);
		std::function<void(EventArgs *)> ReturnEventLamdaKeyDown(SDL_Keycode type);
		std::function<void(EventArgs *)> ReturnEventLamdaUp();
		// std::pair< void*, EventArgKeyDown> mFp_InputAction; //Illegal http://www.parashift.com/c++-faq-lite/cant-cvt-memfnptr-to-voidptr.html
		std::pair<std::function<void(EventArgs *)>, EventArgs * > mFp_InputAction ;
	private:
		InputComponent();
		MoveComponent & m_MoveComponent;
		StateComponent & m_StateComponent; 
		//bool m_WasKeyDown, m_WasKeyUp;
		SDL_Event m_event;
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		InputManager * m_InputManager; 
		PlayerInputKeyEvents * m_Events; 
		EventArgKeyDown m_EventArg; 
		
	};

}