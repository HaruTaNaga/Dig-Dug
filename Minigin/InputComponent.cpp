#pragma once
#include "MiniginPCH.h"
#include "InputComponent.h"
#include "SDL.h"
void dae::InputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	bool KeyWasDownThisFrame = false;

	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
		case SDL_KEYDOWN:
			KeyWasDownThisFrame = true;
			m_LastKeyPressed = m_event.key.keysym.sym;
			break;

		case SDL_KEYUP:
			if (m_LastKeyPressed == m_event.key.keysym.sym) {  KeyUp(); m_LastKeyPressed = (SDL_Keycode)0; }
			else if (!KeyWasDownThisFrame && m_KeyPressedTimer < 0) { KeyUp(); m_LastKeyPressed = (SDL_Keycode)0;}
			break;
		}
	}
	if (m_KeyPressedTimer >= 0)
		m_KeyPressedTimer += deltaTime;
	if (m_KeyPressedTimer >= 0.5)
		m_KeyPressedTimer = -1; 

	if (KeyWasDownThisFrame)
		KeyDown();

	
}

void dae::InputComponent::KeyUp()
{
	m_Events.KeyUp.Execute(m_EventArg);
}

void dae::InputComponent::KeyDown()
{
	m_KeyPressedTimer = 0;
	switch (m_LastKeyPressed)
	{
	case SDLK_LEFT:
		m_Events.KeyDownLeft.Execute(m_EventArg); 
		break;

	case SDLK_RIGHT:
		m_Events.KeyDownRight.Execute(m_EventArg);
		break;

	case SDLK_UP:
		m_Events.KeyDownUp.Execute(m_EventArg);
		break;

	case SDLK_DOWN:
		m_Events.KeyDownDown.Execute(m_EventArg);
		break;

	}
}
