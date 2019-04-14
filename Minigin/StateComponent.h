#pragma once
#include "BaseComponent.h"
namespace dae {

	class StateComponent : BaseComponent
	{
	public: 
		StateComponent();
		virtual ~StateComponent() {};
	private: 

	protected: 
		virtual void Derp();
	};
}