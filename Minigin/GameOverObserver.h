#pragma once
#include "IObserver.h"
namespace dae
{
	class GameOverObserver : public IObserver
	{
	public: 

		GameOverObserver() {};
		~GameOverObserver() {};
		void Notify(dae::EventTypes  eType )override;

	

	};
}
