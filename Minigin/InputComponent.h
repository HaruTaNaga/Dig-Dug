#pragma once
#include <XInput.h>
#include "BaseComponent.h"
#include "MoveComponent.h"
#include "SDL.h"
#include "PlayerInputEvents.h"
namespace dae {

	class InputComponent final : public BaseComponent
	{
	public:

		InputComponent(MoveComponent & mc, std::shared_ptr<GameObject> owner) : BaseComponent(owner), m_MoveComponent(mc) , m_EventArg(mc) {};
		~InputComponent() {};
		void Update(float deltaTime) override;
		void KeyDown();
		void KeyUp();
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::inputComp; }
		//MoveComponent & GetInputComponent() { return mMoveComponent;  }
	private:
		InputComponent();
		MoveComponent & m_MoveComponent;
		//XINPUT_STATE currentState{};
		SDL_Event m_event;
		int m_AmountOfKeysPressed = 0; 
		SDL_Keycode m_LastKeyPressed;
		float m_KeyPressedTimer = -1; 
		PlayerInputKeyEvents m_Events; 
		EventArgKeyDown m_EventArg; 
	};

}