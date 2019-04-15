#pragma once
#include <XInput.h>
#include "BaseComponent.h"
#include "MoveComponent.h"
#include "SDL.h"
#include "PlayerInputEvents.h"
#include "InputManager.h"
#include <functional>
namespace dae {

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
		InputComponent(MoveComponent & mc, std::shared_ptr<GameObject> owner)  ;
		~InputComponent() {};
		void Update(float deltaTime) override;
		void KeyDown();
		void KeyUp();
		bool m_WasKeyDown, m_WasKeyUp;
		std::function<void(EventArgs *)> ReturnEmptyEventLamda();
		std::function<void(EventArgs *)> ReturnEventLamda(EventTypesEnum type);
		// std::pair< void*, EventArgKeyDown> mFp_InputAction; //Illegal http://www.parashift.com/c++-faq-lite/cant-cvt-memfnptr-to-voidptr.html
		std::pair<std::function<void(EventArgs *)>, EventArgs * > mFp_InputAction ;
	private:
		InputComponent();
		MoveComponent & m_MoveComponent;
		//bool m_WasKeyDown, m_WasKeyUp;
		SDL_Event m_event;
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		InputManager * m_InputManager; 
		PlayerInputKeyEvents * m_Events; 
		EventArgKeyDown m_EventArg; 
		
	};

}