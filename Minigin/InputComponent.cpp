#pragma once
#include "MiniginPCH.h"
#include "ComponentsH.h"
#include "SDL.h"
#include "ServiceLocator.h"
#include "PlayerStates.h"
#include <functional>
dae::InputComponent::InputComponent(MoveComponent & mc, StateComponent & sc, std::shared_ptr<GameObject> owner)
	: BaseComponent(owner),
	m_MoveComponent(mc),
	m_StateComponent(sc),
	m_EventArg(mc), 
	m_Events(new PlayerInputKeyEvents()),
	mFp_InputAction(std::make_pair(std::function<void(EventArgs *)>(ReturnEmptyEventLamda()), &m_EventArg))
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
	mFp_InputAction.first = std::function<void(EventArgs*)>(ReturnEventLamdaUp());
	m_StateComponent.NotifyonEvent(mFp_InputAction);
}

std::function<void(dae::EventArgs *)> dae::InputComponent::ReturnEmptyEventLamda()
{
	 return [](EventArgs * ) {return; }; 
}
/*
std::function<void(dae::EventArgs *)> dae::InputComponent::ReturnEventLamda(EventTypesEnum Type)
{
	switch (Type)
	{
	case Right:
		return [](EventArgs * arg){	dynamic_cast<EventArgKeyDown * >(arg)->MComp.SetVelocity(g_runspeed, 0);};
		
		break; 
	case Left: 
		return [](EventArgs * arg) {	dynamic_cast<EventArgKeyDown *>(arg)->MComp.SetVelocity(-g_runspeed, 0); };
		break;
	case Up: 
		return [](EventArgs * arg) {	dynamic_cast<EventArgKeyDown *>(arg)->MComp.SetVelocity( 0,-g_runspeed); };
		break;
	case Down: 
		return [](EventArgs * arg) {	dynamic_cast<EventArgKeyDown *>(arg)->MComp.SetVelocity(0, g_runspeed); };
		break; 
	case Empty:
		return [](EventArgs * ) {return; };
		break;
	case KeyReleased:
		return [](EventArgs * arg) {	dynamic_cast<EventArgKeyDown *>(arg)->MComp.SetVelocity(0, 0); };
		break;
	}
		

	return [](EventArgs * ) {return; };
}
*/
std::function<void(dae::EventArgs*)> dae::InputComponent::ReturnEventLamdaKeyDown(SDL_Keycode type)
{
	switch (type)
	{
	case SDLK_RIGHT:
		return [](EventArgs * arg) {	(arg)->MComp.SetVelocity(g_runspeed, 0); };

		break;
	case SDLK_LEFT:
		return [](EventArgs * arg) {	(arg)->MComp.SetVelocity(-g_runspeed, 0); };
		break;
	case SDLK_UP:
		return [](EventArgs * arg) {	(arg)->MComp.SetVelocity(0, -g_runspeed); };
		break;
	case SDLK_DOWN:
		return [](EventArgs * arg) {	(arg)->MComp.SetVelocity(0, g_runspeed); };
		break;
	default:
		return [](EventArgs *) {return; };
		break;
	}
}
std::function<void(dae::EventArgs*)> dae::InputComponent::ReturnEventLamdaUp()
{
	return [](EventArgs * arg) {	(arg)->MComp.SetVelocity(0, 0); };
}
void dae::InputComponent::KeyDown()
{
	//StandardSArg s;  
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
	switch (m_LastKeyPressed)
	{
	case SDLK_RIGHT:
		mFp_InputAction.first = std::function<void(EventArgs* )>(ReturnEventLamdaKeyDown(SDLK_RIGHT));
		
		break;

	case SDLK_LEFT :
		mFp_InputAction.first = std::function<void(EventArgs*)>(ReturnEventLamdaKeyDown(SDLK_LEFT));
		
		break;

	case SDLK_UP:
		mFp_InputAction.first = std::function<void(EventArgs*)>(ReturnEventLamdaKeyDown(SDLK_UP));
		break;

	case SDLK_DOWN:
		mFp_InputAction.first = std::function<void(EventArgs*)>(ReturnEventLamdaKeyDown(SDLK_DOWN));
		break;
	}
	m_StateComponent.NotifyonEvent(mFp_InputAction);
}
