#include "MiniginPCH.h"
#include "EnemyDeathObserver.h"
#include "ServiceLocator.h"
void dae::EnemyDeathObserver::Notify(dae::EventTypes  eType)
{
	switch (eType)
	{
	case EventTypes::EnemyDied:
			//const auto scoremgr = ServiceLocator::GetScoreManager(); 
			
			break;

	}
}
