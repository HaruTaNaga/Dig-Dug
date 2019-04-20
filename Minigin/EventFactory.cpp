#include "MiniginPCH.h"
#include "EventFactory.h"
#include "PlayerStates.h"
#include "MoveComponent.h"
#include "ComponentsH.h"
#include <functional>
dae::EventFactory::~EventFactory()
{
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEventLamdaKeyDown(SDL_Keycode type)
{
	switch (type)
	{
	case SDLK_RIGHT:
		return [](EventArgs * arg)
		{	(arg)->MComp.get().SetVelocity(g_runspeed, 0); 
		arg->AComp->isFlipped = false;
		arg->AComp->m_ActiveAnimationId = 6; 
		};

		break;
	case SDLK_LEFT:
		return [](EventArgs * arg) 
		{
			(arg)->MComp.get().SetVelocity(-g_runspeed, 0);
			arg->AComp->isFlipped = true;
			arg->AComp->m_ActiveAnimationId = 7;  
		};
		break;
	case SDLK_UP:
		return [](EventArgs * arg) 
		{
			(arg)->MComp.get().SetVelocity(0, -g_runspeed);
			if (arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 11;
			arg->AComp->m_ActiveAnimationId = 9; 
		};
		break;
	case SDLK_DOWN:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, g_runspeed);
			if (arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 10;
			arg->AComp->m_ActiveAnimationId = 8; 
		};
		break;
	case SDLK_f:
		return [](EventArgs * arg)
		{	
			(arg)->PComp.get().SetPosition(glm::vec3(0,0,0)); };
		break;
	case SDLK_s:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, g_runspeed); 
		};
		break;
	default:
		return [](EventArgs *) {return; };
		break;
	}
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEventLamdaUp(SDL_Keycode type)
{
/*	return [](EventArgs * arg)
	{
		(arg)->MComp.get().SetVelocity(0, 0); arg->AComp->m_ActiveAnimationId = 0; arg->AComp->m_CurrentFrame = 0; 
	}; */

	switch (type)
	{
	case SDLK_RIGHT:
		return [](EventArgs * arg)
		{	(arg)->MComp.get().SetVelocity(0, 0); arg->AComp->m_ActiveAnimationId = 0; arg->AComp->m_CurrentFrame = 0;
		};

		break;
	case SDLK_LEFT:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0); arg->AComp->m_ActiveAnimationId = 1; arg->AComp->m_CurrentFrame = 0;
		};
		break;
	case SDLK_DOWN:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0); arg->AComp->m_ActiveAnimationId = 2; arg->AComp->m_CurrentFrame = 0;
		};
		break;
	case SDLK_UP:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0); arg->AComp->m_ActiveAnimationId = 3; arg->AComp->m_CurrentFrame = 0;
		};
		break;


	}

	return [](EventArgs * arg)
	{
		(arg)->MComp.get().SetVelocity(0, 0);  arg->AComp->m_CurrentFrame = 0;
	};
}

std::function<void(dae::EventArgs *)> dae::EventFactory::ReturnEmptyEventLamda()
{
	return [](EventArgs *) {return; };
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnDeathEvent()
{
	return [](EventArgs * arg)
	{
		arg->DComp->NotifyOnDeath();
		arg->MComp.get().SetVelocity(0, 0); 
		arg->AComp->m_CurrentFrame = 0;
		arg->AComp->m_ActiveAnimationId = 13;
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnRespawnEvent()
{
	return [](EventArgs * arg)
	{	
		(arg)->PComp.get().SetPosition(glm::vec3(0, 96, 0));
		arg->AComp->m_ActiveAnimationId = 0;
		arg->AComp->m_CurrentFrame = 0;
		arg->DComp->m_HasDied = false; 
	};
}