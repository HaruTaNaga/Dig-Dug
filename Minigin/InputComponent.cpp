#pragma once
#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "SDL.h"
#include "ServiceLocator.h"
#include "States.h"
#include <functional>
#include "cArgs.h"
dae::InputComponent::InputComponent( StateComponent & sc, CommandComponent & commandcomp, PlayerTypes playerId)
	: 
	m_StateComponent(sc),
	m_CommandComponent(commandcomp)
{
	m_InputManager = ServiceLocator::GetInputManager(); 
	m_PlayerId = playerId;
}
void dae::InputComponent::Update(float )
{
	m_WasKeyDown = false; 
	if (m_InputManager->m_WasKeyDownThisFrame)
		KeyDown();
	if (m_InputManager->m_WasKeyUpThisFrame && m_LastKeyPressed == m_InputManager->m_LastKeyUp  && m_PlayerId != PlayerTypes::Menu)
		KeyUp();
}


void dae::InputComponent::KeyUp()
{
	m_LastKeyReleased = m_InputManager->m_LastKeyUp; 
	m_CommandComponent.KeyUp(m_LastKeyReleased);
}


void dae::InputComponent::KeyDown()
{
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
	m_CommandComponent.KeyDown( m_LastKeyPressed, m_PlayerId);
}
