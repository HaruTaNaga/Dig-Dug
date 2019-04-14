#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "SDL.h"
namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final //: public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		//bool IsPressed(ControllerButton button) const;
		bool m_WasKeyDownThisFrame = false;
		bool m_WasKeyUpThisFrame = false;
		SDL_Keycode m_LastKeyDown;
		SDL_Keycode m_LastKeyUp;
	private:
		XINPUT_STATE currentState{};

	};

}
