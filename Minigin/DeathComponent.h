#pragma once
#include  "ComponentsH.h"

namespace dae {


	class DeathComponent : public  BaseComponent {
	public:
		DeathComponent() {};
		~DeathComponent() {}; 
		void Update(float deltaTime) override;
		void NotifyOnDeath();


	};

}