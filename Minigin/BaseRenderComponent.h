#pragma once
#include "ComponentsH.h"
namespace dae {

	class BaseRenderComponent : public BaseComponent {
	public: 
		BaseRenderComponent() = default ; 
		virtual ~BaseRenderComponent() {};
		virtual void Render () {};
	};
}