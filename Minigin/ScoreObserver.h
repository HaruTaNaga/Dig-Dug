#pragma once
#include "IObserver.h"
namespace dae
{
	class ScoreObserver : public IObserver
	{
	public:

		ScoreObserver() {};
		~ScoreObserver() {};
		void Notify(dae::EventTypes  eType)override;



	};
}
