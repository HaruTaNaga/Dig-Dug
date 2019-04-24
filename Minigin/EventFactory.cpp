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
			if (!arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 11;
			else
			arg->AComp->m_ActiveAnimationId = 9; 
		};
		break;
	case SDLK_DOWN:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, g_runspeed);
			if (!arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 8;
			else
			arg->AComp->m_ActiveAnimationId = 10; 
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
		{	
			(arg)->MComp.get().SetVelocity(0, 0);
		arg->AComp->m_ActiveAnimationId = 0; 
		arg->AComp->m_CurrentFrame = 0;
		};

		break;
	case SDLK_LEFT:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0); 
			arg->AComp->m_ActiveAnimationId = 1; 
			arg->AComp->m_CurrentFrame = 0;
		};
		break;
	case SDLK_DOWN: //TODO FLIPPED IDLE 
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0);
			if (arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 4;
			else 
				arg->AComp->m_ActiveAnimationId = 2; 
			arg->AComp->m_CurrentFrame = 0;
		};
		break;
	case SDLK_UP:
		return [](EventArgs * arg)
		{
			(arg)->MComp.get().SetVelocity(0, 0);
			if (!arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 5;
			else
			arg->AComp->m_ActiveAnimationId = 3;
			arg->AComp->m_CurrentFrame = 0;
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
		//arg->PumpComp.get().NotifyOnPumpEnd();
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnRespawnEvent()
{
	return [](EventArgs * arg)
	{	
		arg->MComp.get().SetVelocity(0, 0);
		arg->MComp.get().m_PositionComponent.SetPosition(glm::vec3(0, 96, 0));
		arg->AComp->m_ActiveAnimationId = 0;
		arg->AComp->m_CurrentFrame = 0;
		arg->DComp->m_HasDied = false; 
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnGameOverEvent()
{
	return [](EventArgs * arg)
	{
		arg->PComp.get().SetPosition(glm::vec3(9999, 9999, 0));
		arg->AComp->m_ActiveAnimationId = 0;
		arg->AComp->m_CurrentFrame = 0;
		arg->DComp->m_HasDied = false;
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnPumpLaunchEvent()
{
	
	return [](EventArgs * arg)
	{
		arg->MComp.get().SetVelocity(0, 0);
		if (arg->PumpComp.get().m_Hose.hasConnected)
		{
			//arg->AComp->m_CurrentFrame++;
			arg->PumpComp.get().NotifyOnPumping();
		}
		else
		{ 
		switch (arg->PumpComp.get().m_OrientationComp.GetOrientation())
		{
		case Orientation::Right :
			arg->AComp->m_ActiveAnimationId = 15;
			break; 
		case Orientation::Left:
			arg->AComp->m_ActiveAnimationId = 16;
			break;
		case Orientation::Bottom:
			if (arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 19;
			else
				arg->AComp->m_ActiveAnimationId = 17;
			break;
		case Orientation::Top:
			if (!arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 20;  
			else 
				arg->AComp->m_ActiveAnimationId = 18;
			break;

		}
		//Set Animation to pump animation, 
		//arg->AComp->m_ActiveAnimationId = 0;
		arg->AComp->m_CurrentFrame = 0;
		arg->PumpComp.get().NotifyOnPumpLaunch();
		}
		//arg->DComp->m_HasDied = false;
		
	};

	
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnPumpEndEvent()
{
	return [](EventArgs * arg)
	{ //Acts on Player (Pump) 
		arg->AComp->FreezeAnimation = false;
		arg->AComp->m_CurrentFrame = 0;
		switch (arg->PumpComp.get().m_OrientationComp.GetOrientation())
		{
		case Orientation::Right:
			arg->AComp->m_ActiveAnimationId = 0;
			break;
		case Orientation::Left:
			arg->AComp->m_ActiveAnimationId = 1;
			break;
		case Orientation::Bottom:
			if (arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 4;
			else
				arg->AComp->m_ActiveAnimationId = 2;
			break;
		case Orientation::Top:
			if (!arg->AComp->isFlipped)
				arg->AComp->m_ActiveAnimationId = 5;
			else
				arg->AComp->m_ActiveAnimationId = 3;
			break;
		}
		arg->PumpComp.get().NotifyOnPumpEnd();
	};
}


std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnHoseLaunchEvent()
{

	return [](EventArgs * arg)
	{ //Acts on hose
		auto pos = arg->HoseComp.get().m_PlayerPositionCmp->GetPosition();
		arg->AComp->FreezeAnimation = false;
		arg->AComp->m_ActiveAnimationId = 0;
		arg->AComp->m_CurrentFrame = 0;
			switch (arg->HoseComp.get().m_PlayerOrientationCmp->GetOrientation())
			{
			case Orientation::Right:
				arg->HoseComp.get().m_OrientationComp.m_Orientation = Right;
				arg->AComp->m_ActiveAnimationId = 0;
				pos.x += 32; 
				pos.y += 16; 
				break;
			case Orientation::Left:
				arg->HoseComp.get().m_OrientationComp.m_Orientation = Left;
				arg->AComp->m_ActiveAnimationId = 1;
				//pos.x -= 2;
				pos.y += 16;
				break;
			case Orientation::Bottom:
				arg->HoseComp.get().m_OrientationComp.m_Orientation = Bottom;
				arg->AComp->m_ActiveAnimationId = 2;
				if (!arg->AComp->isFlipped)
				pos.x += 16;
				pos.y += 32;
				break;
			case Orientation::Top:
				arg->HoseComp.get().m_OrientationComp.m_Orientation = Top;
				arg->AComp->m_ActiveAnimationId = 3;
				if (!arg->AComp->isFlipped) // TODO LINK PLAYER ANIMATION FLIPPING TO HOSE POSITION (sync hose animationcomp m_isflipped ) 
					pos.x += 16;
				//pos.y -= 2;
				break;

			}
			arg->PComp.get().SetPosition(pos);
			
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnHoseEndEvent()
{
	return [](EventArgs * arg)
	{ //Acts on hose
		arg->PComp.get().SetPosition(0, 0, 0); 
		arg->AComp->FreezeAnimation = false;
		arg->AComp->m_ActiveAnimationId = 0;
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnHoseHitEvent()
{
	return [](EventArgs * arg)
	{ //Acts on hose
		arg->HoseComp.get().NotifyOnPumpHit(); 
		arg->AComp->FreezeAnimation = true; 
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyHitEvent()
{
	return [](EventArgs * arg)
	{
		//Acts on enemy
		static_cast<CollisionComponent *>(arg->StateComp.get().m_EventGenComponent.m_Owner.GetComponent<CollisionComponent>())->m_CanCollide = false;
		arg->AComp->m_ActiveAnimationId = 4; 
		arg->AComp->FreezeAnimation = true;
	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnStartPumpingEnemyEvent()
{
	return [](EventArgs * arg)
	{ //Acts on player
		arg->AComp->FreezeAnimation = true;
	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnPlayerPumpingEnemyEvent()
{
	return [](EventArgs * arg)
	{ //Acts on player
		arg->AComp->FreezeAnimation = true;
		auto frame = arg->AComp->m_CurrentFrame; 
		frame++; 
		frame = frame % 2; 
		arg->AComp->m_CurrentFrame = frame; 
		
	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyPumpedEvent()
{
	return [](EventArgs * arg)
	{ //Acts on player
		arg->AComp->FreezeAnimation = true;
		auto frame = arg->AComp->m_CurrentFrame;
		frame++;
		if (frame == arg->AComp->m_Animations[arg->AComp->m_ActiveAnimationId].m_AmountOfFrames) 
		{
			arg->StateComp.get().m_EventGenComponent.GenerateEnemyExplodeEvent();
		}
			//TODO: die
		else
		{
			arg->AComp->m_CurrentFrame = frame;
		}
		//frame = frame % ;
		

	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyDeflationEvent()
{
	return [](EventArgs * arg)
	{	
		auto frame = arg->AComp->m_CurrentFrame;
		frame--;
		if (frame == 0) { 
			//arg->EventType = EventTypes::EnemyDeflated;
			arg->StateComp.get().m_EventGenComponent.GenerateEnemyDeflatedEvent();
		}
		else
			arg->AComp->m_CurrentFrame = frame;
	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyDeflatedEvent()
{
	return [](EventArgs * arg)
	{
		static_cast<CollisionComponent *>(arg->StateComp.get().m_EventGenComponent.m_Owner.GetComponent<CollisionComponent>())->m_CanCollide = true; 
		arg->AComp->FreezeAnimation = false; 
		arg->AComp->m_ActiveAnimationId = 0;
	};
}
std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyDeathEvent()
{
	return [](EventArgs * arg)
	{
		arg->AComp->FreezeAnimation = true;
		arg->AComp->m_ActiveAnimationId = 5;
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyDespawnEvent()
{
	return [](EventArgs * arg)
	{
		arg->PComp.get().SetPosition(999, 999, 0);
		
	};
}

std::function<void(dae::EventArgs*)> dae::EventFactory::ReturnEnemyCrushedEvent()
{
	return [](EventArgs * arg)
	{
		arg->AComp->m_ActiveAnimationId = 6;

	};
}