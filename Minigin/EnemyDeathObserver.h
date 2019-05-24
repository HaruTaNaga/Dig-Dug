#pragma once
#include  "IObserver.h"
namespace dae {
	class EnemyDeathObserver : public IObserver
	{
	public: 
		EnemyDeathObserver() {};
		~EnemyDeathObserver() {};
		void Notify(dae::EventTypes  eType) override;



	};
}