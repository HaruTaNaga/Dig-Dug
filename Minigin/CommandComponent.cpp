#include "MiniginPCH.h"
#include "CommandComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"

dae::CommandComponent::CommandComponent(GameObject & go) : m_Owner(go)
{
	
	m_CommandFactory = ServiceLocator::GetCommandFactory(); 
	m_cArg.reset(new cArgs());
	m_Pair_Command_Args = std::make_pair< std::function< void(cArgs*) > , cArgs*> ( [] (cArgs *) {} , m_cArg.get());
	
}

void dae::CommandComponent:: Empty ()
{
	m_Pair_Command_Args.first = m_CommandFactory->EmptyLamda();
	m_Pair_Command_Args.second->MComp =m_MoveComponent;
	NotifyState();
}

void dae::CommandComponent:: KeyDown(SDL_Keycode  key, PlayerIdentifier id)
{
	
	switch (id)
	{
	case PlayerOne:
	case PlayerTwo:
		if (key == SDLK_o)
		{
			ServiceLocator::GetSceneManager()->SetActiveScene(0);
			return;
		}
		if (key == SDLK_p)
		{
			ServiceLocator::GetSceneManager()->SetActiveScene(1);
			return;
		}
		if (key == SDLK_RIGHT || key == SDLK_LEFT ||
			key == SDLK_DOWN || key == SDLK_UP)
		{
			m_Pair_Command_Args.second->MComp = m_MoveComponent;
			m_Pair_Command_Args.second->AComp = m_AnimationComponent;
			m_Pair_Command_Args.second->commandType = CommandTypes::Moving;
		}
		else if (key == SDLK_f || key == SDLK_RCTRL)
		{
			 PumpLaunch();
			return;
		}

		break;
	case  Fygar:
		if (key == SDLK_RIGHT || key == SDLK_LEFT ||
			key == SDLK_DOWN || key == SDLK_UP)
		{
			m_Pair_Command_Args.second->MComp = m_MoveComponent;
			m_Pair_Command_Args.second->AComp = m_AnimationComponent;
			m_Pair_Command_Args.second->commandType = CommandTypes::Moving;
		}

		break;

	}
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->KeyDown(key));
	NotifyState();
	
}

void dae::CommandComponent:: KeyUp(SDL_Keycode type)
{
	m_Pair_Command_Args.second->commandType = CommandTypes::Moving;
	m_Pair_Command_Args.second->MComp = m_MoveComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->KeyUp(type));
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	NotifyState();
}

void  dae::CommandComponent:: Death()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::Dying;
	m_Pair_Command_Args.second->DComp = m_DeathComponent;
	m_Pair_Command_Args.first =  std::function<void(cArgs*)>(m_CommandFactory->Death());
	NotifyState();
}

void dae::CommandComponent:: Respawn()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::Respawning;
	m_Pair_Command_Args.second->MComp =m_MoveComponent;

	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->Respawn());
	NotifyState();
	
}

void dae::CommandComponent:: GameOver()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::GameOver;
	m_Pair_Command_Args.second->PComp =m_PositionComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->GameOver());
	NotifyState();
}
void dae::CommandComponent:: PumpLaunch()
{
	//set state to pump state
	
	m_Pair_Command_Args.second->commandType = CommandTypes::StartPump;
	m_Pair_Command_Args.second->PComp = m_PositionComponent;
	m_Pair_Command_Args.second->PumpComp =m_PumpComponent;
	m_Pair_Command_Args.second->MComp = m_MoveComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->PumpLaunch());
	NotifyState();
}
void dae::CommandComponent:: PumpEnd()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EndPump;
	m_Pair_Command_Args.second->PComp = m_PositionComponent;
	m_Pair_Command_Args.second->PumpComp =m_PumpComponent;

	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->PumpEnd());
	NotifyState();

}


void dae::CommandComponent:: HoseLaunch()
{
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.second->commandType = CommandTypes::LaunchHose;
	m_Pair_Command_Args.second->PComp = m_PositionComponent;
  
	m_Pair_Command_Args.second->HoseComp =m_HoseComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->HoseLaunch());
	NotifyState();
}
void dae::CommandComponent:: HoseEnd()
{ 
	m_Pair_Command_Args.second->commandType = CommandTypes::HoseEnd;
	m_Pair_Command_Args.second->HoseComp     =m_HoseComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->HoseEnd());
	NotifyState ();
}
void dae::CommandComponent:: HoseHit (GameObject * HitEnemy)
{
	//acts on hose
	m_HoseComponent->ConnectEnemy(HitEnemy);
	m_Pair_Command_Args.second->commandType = CommandTypes::HoseHit;
	m_Pair_Command_Args.second->HoseComp = m_HoseComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->HoseHit ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyHit ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyHit;
	m_Pair_Command_Args.second->StateComp = m_StateComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.second->MComp = m_MoveComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyHit ());

	NotifyState ();
}
void dae::CommandComponent:: StartPumpingEnemy ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::PlayerHitEnemy;

	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->StartPumpingEnemy ());
	NotifyState ();
}
void dae::CommandComponent:: PlayerPumping ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::PlayerPumping;

	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->PlayerPumpingEnemy ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyPumped ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyPumped;
	m_Pair_Command_Args.second->StateComp = m_StateComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyPumped ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyDeflate ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyDeflating;
	m_Pair_Command_Args.second->StateComp = m_StateComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyDeflation ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyDeflated ()
{

	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyDeflated;
	m_Pair_Command_Args.second->StateComp = m_StateComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyDeflated ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyExplode ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyDeath;
	m_Pair_Command_Args.second->StateComp =m_StateComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyDeath ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyDespawn ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyDespawn;
	m_Pair_Command_Args.second->PComp = m_PositionComponent;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyDespawn ());
	NotifyState ();
}
void dae::CommandComponent:: EnemyCrushed ()
{
	m_Pair_Command_Args.second->commandType = CommandTypes::EnemyCrushed;
	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
	m_Pair_Command_Args.first = std::function<void(cArgs*)>(m_CommandFactory->EnemyCrushed());
	NotifyState();

}
void dae::CommandComponent::NotifyState()
{

	m_StateComponent->Notify(Command(m_Pair_Command_Args));
	
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

	m_Pair_Command_Args.second->AComp = m_AnimationComponent;
}
