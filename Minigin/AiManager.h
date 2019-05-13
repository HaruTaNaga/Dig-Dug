#pragma once
#include  <vector>
namespace dae {
	class GameObject; 
	class PositionComponent; 
	class MapTile; 
	
	class  AiManager {
	public: 
		AiManager();
		~AiManager() {};

		std::pair<bool, dae::Vec2>  CalculateNewDestination(Vec2 enemyPos);
		std::pair<bool, dae::Orientation> CalculateNewDirection(Vec2 enemyPos);
		std::pair<bool, dae::Vec2>  CheckDir(dae::MapTile const &  m_Edge, dae::Orientation dir) const;
		//void InitPlayerPos
		void LinkNewPlayerPosCmp(PositionComponent * posCmp) { m_PlayerPosComp.push_back(posCmp); };
		void  ClearTrackedPlayers() { m_PlayerPosComp.clear(); };

		std::vector<PositionComponent *> m_PlayerPosComp; 

	};
}