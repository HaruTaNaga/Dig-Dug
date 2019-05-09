#pragma once
#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "SDL.h"
#include "ServiceLocator.h"
#include "States.h"
#include <functional>
#include "cArgs.h"
dae::InputComponent::InputComponent( StateComponent & sc, CommandComponent & eventcomp, PlayerIdentifier playerId)
	: 
	m_StateComponent(sc),
	m_CommandComponent(eventcomp)
{
	m_InputManager = ServiceLocator::GetInputManager(); 
	m_PlayerId = playerId;
}
void dae::InputComponent::Update(float )
{
	m_WasKeyDown = false; 
	if (m_InputManager->m_WasKeyDownThisFrame)
		KeyDown();
	if (m_InputManager->m_WasKeyUpThisFrame && m_LastKeyPressed == m_InputManager->m_LastKeyUp)
		KeyUp();
}


void dae::InputComponent::KeyUp()
{
	m_LastKeyPressed = (SDL_Keycode)0;
	m_LastKeyReleased = m_InputManager->m_LastKeyUp; 
	m_CommandComponent.GenerateKeyUpEvent(m_InputManager->m_LastKeyUp);
}


void dae::InputComponent::KeyDown()
{
 
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
	m_CommandComponent.GenerateKeyDownEvent( m_LastKeyPressed, m_PlayerId);
}
