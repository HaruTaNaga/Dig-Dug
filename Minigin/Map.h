#pragma once
#include "MapTile.h"
#include "MapTileEdge.h"
#include  "SDL_rect.h"
namespace dae
{
	class Renderer;
	class Map {
	public: 
		Map(); 
		~Map();
		void LoadMap(dae::Levels Level);
		std::vector<std::vector<MapTile>> m_Tiles; 
		std::vector<std::unique_ptr<MapTileEdge>> m_TileEdges;
		MapTileEdge * GetMapTileEdgeFromCoord(Vec2 pos, dae::Orientation orientation);
		MapTile & GetTileFromCoord(int x, int y);
		//Debug Rendering
		Renderer* m_Renderer;
		SDL_Rect * r = nullptr;
	};
}