#include "MiniginPCH.h"
#include "CommandComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"

dae::CommandComponent::CommandComponent(GameObject & go) : m_Owner(go)
{
	
	m_EventFactory = ServiceLocator::GetEventFactory(); 
	//auto sc = m_Owner.GetComponent<StateComponent>();
	/*
	m_StateComponent = static_cast<StateComponent *>(m_Owner.GetComponent<StateComponent>());
	m_MoveComponent = static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>());
	m_AnimationComponent = static_cast<AnimationComponent *>(m_Owner.GetComponent<AnimationComponent>());
	m_DeathComponent = static_cast<DeathComponent *> (m_Owner.GetComponent<DeathComponent>()); 
	m_PumpComponent = static_cast<PumpComponent *>(m_Owner.GetComponent<PumpComponent>()); 
	*/
	m_EventArg.reset(new cArgs());
	m_FpPairEventArg = std::make_pair<std::function<void(cArgs *)>, cArgs * >([](cArgs *) {}, m_EventArg.get()); 
	
}

void dae::CommandComponent::GenerateEmptyEvent()
{
	m_FpPairEventArg.first = m_EventFactory->ReturnEmptyEventLamda();
	m_FpPairEventArg.second->MComp =m_MoveComponent;
	NotifyStateEvent();
}

void dae::CommandComponent::GenerateKeyDownEvent(SDL_Keycode  key, PlayerIdentifier id)
{
	
	switch (id)
	{
	case PlayerOne:
	case PlayerTwo:
		if (key == SDLK_RIGHT || key == SDLK_LEFT ||
			key == SDLK_DOWN || key == SDLK_UP)
		{
			m_FpPairEventArg.second->MComp = m_MoveComponent;
			m_FpPairEventArg.second->AComp = m_AnimationComponent;
			m_FpPairEventArg.second->commandType = CommandTypes::Moving;
		}
		else if (key == SDLK_f || key == SDLK_RCTRL)
		{
			GeneratePumpLaunchEvent();
			return;
		}

		break;
	case  Fygar:
		if (key == SDLK_RIGHT || key == SDLK_LEFT ||
			key == SDLK_DOWN || key == SDLK_UP)
		{
			m_FpPairEventArg.second->MComp = m_MoveComponent;
			m_FpPairEventArg.second->AComp = m_AnimationComponent;
			m_FpPairEventArg.second->commandType = CommandTypes::Moving;
		}

		break;

	}
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEventLamdaKeyDown(key));
	NotifyStateEvent();
	
}

void dae::CommandComponent::GenerateKeyUpEvent(SDL_Keycode type)
{
	m_FpPairEventArg.second->commandType = CommandTypes::Moving;
	m_FpPairEventArg.second->MComp = m_MoveComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEventLamdaUp(type));
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	NotifyStateEvent();
}

void  dae::CommandComponent::GenerateDeathEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::Dying;
	m_FpPairEventArg.second->DComp = m_DeathComponent; 
	m_FpPairEventArg.second->PumpComp =m_PumpComponent;
	m_FpPairEventArg.first =  std::function<void(cArgs*)>(m_EventFactory->ReturnDeathEvent());
	NotifyStateEvent();
}

void dae::CommandComponent::GenerateRespawnEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::Respawning;
	m_FpPairEventArg.second->MComp =m_MoveComponent;
	//m_FpPairEventArg.second->PComp = std::reference_wrapper<PositionComponent>(*m_PositionComponent);
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnRespawnEvent());
	NotifyStateEvent();
	
}

void dae::CommandComponent::GenerateGameOverEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::GameOver;
	m_FpPairEventArg.second->PComp =m_PositionComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnGameOverEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GeneratePumpLaunchEvent()
{
	//set state to pump state
	//m_FpPairEventArg.second->IsShootingEvent = true ;
	m_FpPairEventArg.second->commandType = CommandTypes::StartPump;
	m_FpPairEventArg.second->PComp = m_PositionComponent;
	m_FpPairEventArg.second->PumpComp =m_PumpComponent;
	m_FpPairEventArg.second->MComp = m_MoveComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnPumpLaunchEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GeneratePumpEndEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EndPump;
	m_FpPairEventArg.second->PComp = m_PositionComponent;
	m_FpPairEventArg.second->PumpComp =m_PumpComponent;

	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnPumpEndEvent());
	NotifyStateEvent();

}


void dae::CommandComponent::GenerateHoseLaunchEvent()
{
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.second->commandType = CommandTypes::LaunchHose;
	m_FpPairEventArg.second->PComp = m_PositionComponent;
  
	m_FpPairEventArg.second->HoseComp =m_HoseComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnHoseLaunchEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateHoseEndEvent()
{ 
	m_FpPairEventArg.second->commandType = CommandTypes::HoseEnd;
	m_FpPairEventArg.second->HoseComp     =m_HoseComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnHoseEndEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateHoseHitEvent(GameObject * HitEnemy)
{
	//acts on hose
	m_HoseComponent->ConnectEnemy(HitEnemy);
	m_FpPairEventArg.second->commandType = CommandTypes::HoseHit;
	m_FpPairEventArg.second->HoseComp = m_HoseComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnHoseHitEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyHitEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyHit;
	m_FpPairEventArg.second->StateComp = m_StateComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.second->MComp = m_MoveComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyHitEvent());

	NotifyStateEvent();
}
void dae::CommandComponent::GenerateStartPumpingEnemyEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::PlayerHitEnemy;

	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnStartPumpingEnemyEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GeneratePlayerPumpingEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::PlayerPumping;

	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnPlayerPumpingEnemyEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyPumpedEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyPumped;
	m_FpPairEventArg.second->StateComp = m_StateComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyPumpedEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyDeflateEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyDeflating;
	m_FpPairEventArg.second->StateComp = m_StateComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyDeflationEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyDeflatedEvent()
{

	m_FpPairEventArg.second->commandType = CommandTypes::EnemyDeflated;
	m_FpPairEventArg.second->StateComp = m_StateComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyDeflatedEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyExplodeEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyDeath;
	m_FpPairEventArg.second->StateComp =m_StateComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyDeathEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyDespawnEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyDespawn;
	m_FpPairEventArg.second->PComp = m_PositionComponent;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyDespawnEvent());
	NotifyStateEvent();
}
void dae::CommandComponent::GenerateEnemyCrushedEvent()
{
	m_FpPairEventArg.second->commandType = CommandTypes::EnemyCrushed;
	m_FpPairEventArg.second->AComp = m_AnimationComponent;
	m_FpPairEventArg.first = std::function<void(cArgs*)>(m_EventFactory->ReturnEnemyCrushedEvent());
	NotifyStateEvent();

}
void dae::CommandComponent::NotifyStateEvent()
{

	m_StateComponent->NotifyonEvent(Command(m_FpPairEventArg)); 
	//m_FpPairEventArg.second->PComp = std::reference_wrapper<PositionComponent>(*m_PositionComponent);
	//m_FpPairEventArg.second->PumpComp = std::reference_wrapper<PumpComponent>(*m_PumpComponent);
}

void dae::CommandComponent::Update(float )
{
}

void dae::CommandComponent::InitComponents()
{
	m_StateComponent = static_cast<StateComponent *>(m_Owner.GetComponent<StateComponent>());
	m_MoveComponent = static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>());
	m_AnimationComponent = static_cast<AnimationComponent *>(m_Owner.GetComponent<AnimationComponent>());
	m_DeathComponent = static_cast<DeathComponent *> (m_Owner.GetComponent<DeathComponent>());
	m_PumpComponent = static_cast<PumpComponent *>(m_Owner.GetComponent<PumpComponent>());
	m_PositionComponent = static_cast<PositionComponent *>(m_Owner.GetComponent<PositionComponent>());
	m_HoseComponent = static_cast<HoseComponent *>(m_Owner.GetComponent<HoseComponent>());

	m_FpPairEventArg.second->AComp = m_AnimationComponent;
}
