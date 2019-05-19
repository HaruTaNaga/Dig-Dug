#pragma once
namespace dae
{
	class IObserver
	{
	public: 

		IObserver() {};
		virtual ~IObserver() {};
		virtual void Notify(dae::EventTypes  ) {};

	};
}