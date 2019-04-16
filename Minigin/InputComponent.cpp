#pragma once
#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "SDL.h"
#include "ServiceLocator.h"
#include "PlayerStates.h"
#include <functional>
#include "BaseEvent.h"
dae::InputComponent::InputComponent(MoveComponent & mc, StateComponent & sc, EventGenComponent & eventcomp, std::shared_ptr<GameObject> owner)
	: BaseComponent(owner),
	m_MoveComponent(mc),
	m_StateComponent(sc),
	m_EventArg(mc),
	m_EventGenComponent(eventcomp),
//	m_Events(new PlayerInputKeyEvents()),
	m_EventFactory(ServiceLocator::GetEventFactory()),
	mFp_InputAction(std::make_pair([](void *) {}, &m_EventArg))
{
	//mFp_InputAction = std::make_pair(m_Events.KeyUp.Execute, m_EventArg);
	m_InputManager = ServiceLocator::GetInputManager(); 
}
void dae::InputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_WasKeyDown = false; 
	if (m_InputManager->m_WasKeyDownThisFrame)
		KeyDown();

	if (m_InputManager->m_WasKeyUpThisFrame && m_LastKeyPressed == m_InputManager->m_LastKeyUp)
		KeyUp();
}


void dae::InputComponent::KeyUp()
{
	m_LastKeyPressed = (SDL_Keycode)0;
	//m_Events.KeyUp.Execute(m_EventArg);
	//mFp_InputAction.first = std::function<void(EventArgs*)>(ReturnEventLamdaUp());
	//m_EventArg.MComp = std::reference_wrapper<MoveComponent>(m_MoveComponent);
	m_EventGenComponent.GenerateKeyUpEvent(mFp_InputAction); 
	m_StateComponent.NotifyonEvent(mFp_InputAction);
}


void dae::InputComponent::KeyDown()
{
	//StandardSArg s;  
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
	/*
	if (m_LastKeyPressed == SDLK_RIGHT || m_LastKeyPressed == SDLK_LEFT ||
		m_LastKeyPressed == SDLK_DOWN ||  m_LastKeyPressed == SDLK_UP)
	{
		m_EventArg.MComp = std::reference_wrapper<MoveComponent>(m_MoveComponent);
	}
	else if (m_LastKeyPressed == SDLK_f)
	{
		m_EventArg.PComp = std::reference_wrapper<PositionComponent>(m_MoveComponent.m_PositionComponent);
	}
	mFp_InputAction.first = std::function<void(EventArgs* )>(ReturnEventLamdaKeyDown(m_LastKeyPressed));
*/	
	m_EventGenComponent.GenerateKeyDownEvent(mFp_InputAction, m_LastKeyPressed);
	m_StateComponent.NotifyonEvent(mFp_InputAction);
}
