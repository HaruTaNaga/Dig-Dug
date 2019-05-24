#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include "ServiceLocator.h"
void dae::ScoreObserver::Notify(dae::EventTypes eType)
{
	switch(eType)
	{
	case EventTypes::EnemyDied:
		const auto enemymgr = ServiceLocator::GetEnemyManager();
		enemymgr->EnemyKilled();
		if (enemymgr->GetAmountOfEnemies() <= 0)
		{
			auto scenemgr = ServiceLocator::GetSceneManager();
			scenemgr->ResetActiveScene();
			scenemgr->SetActiveScene(1);
		}

		break;

	}
}
