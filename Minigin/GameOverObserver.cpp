#include "MiniginPCH.h"
#include "GameOverObserver.h"
#include "ServiceLocator.h"


void dae::GameOverObserver::Notify(dae::EventTypes  eType )
{
	switch (eType)
	{
		case  PlayerDied:
			ServiceLocator::GetMapManager()->ResetActiveMap(dae::LevelSinglePlayer);
			ServiceLocator::GetSceneManager()->ResetActiveScene();
			ServiceLocator::GetSceneManager()->SetActiveScene(1);
		
		break;

	}
}
