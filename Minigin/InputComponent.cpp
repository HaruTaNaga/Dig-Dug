#pragma once
#include "MiniginPCH.h"
#include "InputComponent.h"
#include "SDL.h"
#include "ServiceLocator.h"
#include "PlayerStates.h"
#include <functional>
dae::InputComponent::InputComponent(MoveComponent & mc, std::shared_ptr<GameObject> owner) 
	: BaseComponent(owner),
	m_MoveComponent(mc),
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
	mFp_InputAction.first = std::function<void(EventArgs  *)>(ReturnEmptyEventLamda());
}

std::function<void(dae::EventArgs *)> dae::InputComponent::ReturnEmptyEventLamda()
{
	 return [](EventArgs * ) {return; }; 
}
std::function<void(dae::EventArgs *)> dae::InputComponent::ReturnEventLamda(EventTypesEnum Type)

{
	switch (Type)
	{
	case Right:
		return [](EventArgs * arg)
		{
			dynamic_cast<EventArgKeyDown * >(arg)->MComp.SetVelocity(g_runspeed, 0);
		};
		
		break; 
	case Left: 
		break;
	case Up: 
		break;
	case Down: 
		break; 
	case Empty:
		return [](EventArgs * ) {return; };
		break;
	case KeyReleased:
		break;
	}
		

	return [](EventArgs * ) {return; };
}
void dae::InputComponent::KeyDown()
{
	//StandardSArg s;  
	m_LastKeyPressed = m_InputManager->m_LastKeyDown;
	switch (m_LastKeyPressed)
	{
	case SDLK_RIGHT:
		mFp_InputAction.first = std::function<void(EventArgs* )>(ReturnEventLamda(EventTypesEnum::Right));
		mFp_InputAction.second = &m_EventArg; 
		//m_Events.KeyDownLeft.Execute(m_EventArg); 
		break;

	case SDLK_LEFT :
		mFp_InputAction.first = std::function<void(EventArgs *)>(ReturnEmptyEventLamda());
		//m_Events.KeyDownRight.Execute(m_EventArg);
		break;

	case SDLK_UP:
		mFp_InputAction.first = std::function<void(EventArgs *)>(ReturnEmptyEventLamda());
		//m_Events.KeyDownUp.Execute(m_EventArg);
		break;

	case SDLK_DOWN:
		mFp_InputAction.first = std::function<void(EventArgs *)>(ReturnEmptyEventLamda());
		//m_Events.KeyDownDown.Execute(m_EventArg);
		break;

	}
}
