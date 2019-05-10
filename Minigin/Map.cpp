#include "MiniginPCH.h"
#include "Map.h"
#include "SDL_render.h"
#include "Renderer.h"
#include "ServiceLocator.h"
dae::Map::Map()
{
	r = new SDL_Rect;
}

dae::Map::~Map()
{
	delete r;
}

void dae::Map::LoadMap(dae::Levels Level)
{
	MapTile m{ };
	m_Renderer = ServiceLocator::GetRenderer();
	switch (Level)
	{
	case Levels::DEMO:
		m_EnableDebugRendering = false;
		m_Tiles = std::vector<std::vector<MapTile>>(g_vertical_blocks, std::vector<MapTile>(g_horizontal_blocks, m));
		for (int y = 0; y < g_vertical_map_blocks; y++)
		{
			for (int x = 0; x < g_horizontal_blocks; x++)
			{
				m_Tiles[y][x].SetPosition(x * 32, (32 * 3) + (32 * y));
				int xpos = x * 32;
				int ypos = (32 * 3) + (32 * y);
				m_Tiles[y][x].SetPosition(xpos, ypos);
			}
		}
		for (int y = 0; y < g_vertical_map_blocks; y++)
		{
			for (int x = 0; x < g_horizontal_blocks; x++)
			{

				if (x < g_horizontal_blocks - 1)
				{
					m_TileEdges.push_back(std::unique_ptr<MapTileEdge>());
					m_TileEdges.at(m_TileEdges.size() - 1).reset(new MapTileEdge(m_Tiles[y][x], m_Tiles[y][1 + x], EdgeDir::Vertical));
					m_Tiles[y][x].m_RightEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
					m_Tiles[y][1 + x].m_LeftEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
				}
				if (y < g_vertical_map_blocks - 1)
				{
					m_TileEdges.push_back(std::unique_ptr<MapTileEdge>());
					m_TileEdges.at(m_TileEdges.size() - 1).reset(new MapTileEdge(m_Tiles[y][x], m_Tiles[1 + y][x], EdgeDir::Horizontal));
					m_Tiles[y][x].m_DownEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
					m_Tiles[1 + y][x].m_UpEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();

				}

			}
		}

		for (int x = 5; x < 10; x++)
		{
			for (int y = 3; y <= 8; y++)
			{
				auto & tile = m_Tiles[y][x];
				tile.m_IsTraversible = true;
				tile.m_RightEdge->IsPassable = true;
				tile.m_UpEdge->IsPassable = true;
			}

		}
		break;
	case Levels::Level1:
		m_Tiles = std::vector<std::vector<MapTile>>(1, std::vector<MapTile>(1, m));
		m_EnableDebugRendering = false; 
		break;
	case Levels::Level2:
		break;

	}
}

dae::MapTile & dae::Map::GetTileFromCoord(int x, int y)
{

	//relationship between location in memory and location on map
	y -= (g_blocksize * g_empty_top_rows); 
	y /= g_blocksize; 
	x /= g_blocksize; 
	if (x < 0 || x >= g_horizontal_blocks || y < 0 || y >= g_vertical_map_blocks)
		return m_Tiles[0][0];
	
	return m_Tiles[y][x];
}
void dae::Map::Render() const noexcept
{
	if (!m_EnableDebugRendering)return; 

	//Debug Rendering
	SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 150, 150, 200, 255);
	for (int y = 0; y < g_vertical_map_blocks; y++)
	{
		for (int x = 0; x < g_horizontal_blocks; x++)
		{
			auto pos = m_Tiles[y][x].m_Position.GetPosition();
			if (!m_Tiles[y][x].m_IsTraversible)
				SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 15, (Uint8)(150), (Uint8)16, 255);
			else
				SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), (Uint8)(150), (Uint8)((0)), (Uint8)15, 255);

			r->x = (int)pos.x - 4 + 16;
			r->y = (int)pos.y - 4 + 16;
			r->h = 8;
			r->w = 8;
			SDL_RenderDrawRect(m_Renderer->GetSDLRenderer(), r);

		}
	}


	for (auto & edge : m_TileEdges)
	{
		auto m1 = edge->m_MapTile1;
		auto m2 = edge->m_MapTile2;
		auto from = m1.m_Position.GetPosition();
		auto to = m2.m_Position.GetPosition();

		auto p1x = 0.0f;
		auto p1y = 0.0f;
		auto p2x = 0.0f;
		auto p2y = 0.0f;

		//Avoid branch prediction 
		auto redmod = ((int)edge->IsPassable * 100);

		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), (Uint8)(15 * redmod), (Uint8)((200 - redmod)), (Uint8)60, 255);

		p1x = edge->ReturnFirstPoint().x;
		p1y = edge->ReturnFirstPoint().y;
		p2x = edge->ReturnSecondPoint().x;
		p2y = edge->ReturnSecondPoint().y;

		SDL_RenderDrawLine(m_Renderer->GetSDLRenderer(), (int)(p1x), (int)(p1y), (int)p2x, (int)p2y);

	}


}

