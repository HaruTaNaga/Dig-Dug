
#pragma once

//#include "MapTile.h"
//#include "MapTileEdge.h"
#include "SceneObject.h"
#include "Map.h"
#include  "SDL_rect.h"
namespace dae {

	class Renderer; 
	class MapManager 
		
	{
	public:
		MapManager();
		~MapManager();
		void LoadMap(dae::Levels Level);
	
		MapTile & GetTileFromCoord(int x, int y);
		std::pair<bool, dae::MapTile*> TryGetTileFromCoord(dae::Vec2 pos);
		void Render() const noexcept  ;
		int m_ActiveLevelid; 
		void SetActiveMap(int id) { m_ActiveLevelid = id;}
		void ResetActiveMap(dae::Levels l) { m_Maps[m_ActiveLevelid]->ResetMap(l); }
		std::vector<std::unique_ptr<Map>> m_Maps; 
	
	};
}


