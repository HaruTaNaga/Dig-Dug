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
		void ResetMap(dae::Levels Level);
		void CreateDefaultMap();
		std::vector<std::vector<MapTile>> m_Tiles; 
		std::vector<std::unique_ptr<MapTileEdge>> m_TileEdges;
		MapTile & GetTileFromCoord(int x, int y);
		std::pair<bool, dae::MapTile *> TryGetTileFromCoord(dae::Vec2  pos);
		//Debug Rendering
		Renderer* m_Renderer;
		SDL_Rect * r = nullptr;
		bool m_EnableDebugRendering = true; 
		MapTile m_Tile; 
		void Render() const noexcept;



	};
}