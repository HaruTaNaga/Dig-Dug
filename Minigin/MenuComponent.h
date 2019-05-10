#pragma once
#include "ComponentsH.h"
#include <vector>
namespace dae {

	class MenuComponent : public BaseComponent
	{
	public: 
		MenuComponent() {};
		~MenuComponent() override {};
		std::vector<std::tuple<Vec2, Levels, int>> m_MenuOptions; 
		void AddMenuOption(Vec2 pos, Levels level , int levelid);
		Vec2 GetPosition() {return std::get<0>(m_MenuOptions[m_ActiveOptionIndex]); }
		int GetNewLevelId() { return std::get<2>(m_MenuOptions[m_ActiveOptionIndex]); }
		void Update(float deltaTime) override;
		int m_ActiveOptionIndex = 0; 
	


	};

}