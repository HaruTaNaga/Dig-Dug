#pragma once
#include "MiniginPCH.h"
#include "InputComponent.h"
#include "SDL.h"
#include "ServiceLocator.h"
dae::InputComponent::InputComponent(MoveComponent & mc, std::shared_ptr<GameObject> owner) 
	: BaseComponent(owner), m_MoveComponent(mc), m_EventArg(mc)
{
	m_InputManager = ServiceLocator::GetInputManager(); 
}
void dae::InputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_InputManager->m_WasKeyDownThisFrame)
		KeyDown();

	if (m_InputManager->m_WasKeyUpThisFrame && m_LastKeyPressed == m_InputManager->m_LastKeyUp)
		KeyUp();
}

void dae::InputComponent::KeyUp()
{
	m_LastKeyPressed = (SDL_Keycode)0;
	m_Events.KeyUp.Execute(m_EventArg);
}

void dae::InputComponent::KeyDown()
{
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
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
