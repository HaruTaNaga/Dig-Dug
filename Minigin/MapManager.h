
#pragma once
#include "Singleton.h"
#include "MapTile.h"
#include "MapTileEdge.h"
#include "SceneObject.h"

#include  "SDL_rect.h"
namespace dae {
	//class SDL_Rect; 
	class Renderer; 
	class MapManager 
		//:public Singleton<MapManager>
	{
	public:
		MapManager();
		~MapManager();
		void LoadMap(dae::Levels Level);
		MapTileEdge * GetMapTileEdgeFromCoord(Vec2 pos, dae::Orientation orientation);
		MapTile & GetTileFromCoord(int x, int y);
		void Render() const ;

		std::vector<std::vector<MapTile>> m_Tiles; 
		std::vector<std::unique_ptr<MapTileEdge>> m_TileEdges; 
		//int EdgeCtr = 0; 
		Renderer* m_Renderer; 
		SDL_Rect * r = nullptr;//ServiceLocator m_ServiceLocator;
	};
}


