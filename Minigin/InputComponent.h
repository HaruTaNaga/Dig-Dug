#pragma once
#include <XInput.h>
#include "BaseComponent.h"
#include "MoveComponent.h"
#include "SDL.h"
#include "PlayerInputEvents.h"
#include "InputManager.h"
namespace dae {

	class InputComponent final : public BaseComponent
	{
	public:

		InputComponent(MoveComponent & mc, std::shared_ptr<GameObject> owner)  ;
		~InputComponent() {};
		void Update(float deltaTime) override;
		void KeyDown();
		void KeyUp();

	private:
		InputComponent();
		MoveComponent & m_MoveComponent;

		SDL_Event m_event;
		SDL_Keycode m_PreviousKeyPressed;
		SDL_Keycode m_LastKeyPressed;
		InputManager * m_InputManager; 
		PlayerInputKeyEvents m_Events; 
		EventArgKeyDown m_EventArg; 
	};

}