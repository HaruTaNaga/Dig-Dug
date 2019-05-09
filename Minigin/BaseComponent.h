#pragma once

namespace dae {

	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;	
		virtual ~BaseComponent() {};
		virtual void Update(float )  {};

	};
}