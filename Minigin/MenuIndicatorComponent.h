#pragma once
#include "ComponentsH.h"
#include <vector>
namespace dae {

	class MenuIndicatorComponent : public BaseComponent
	{
	public: 
		MenuIndicatorComponent() {}; 
		~MenuIndicatorComponent() override {}; 
		std::vector<std::tuple<Vec2, GameModes, Levels>> m_MenuOptions; 
		void AddMenuOption(std::tuple<Vec2, GameModes, Levels>);
		Vec2 GetPosition() {return std::get<0>(m_MenuOptions[m_ActiveOptionIndex]); }
		void Update(float deltaTime) override;
		int m_ActiveOptionIndex = 0; 
	


	};

}