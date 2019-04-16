#include "MiniginPCH.h"
#pragma once
#include "MapManager.h"
#include "SDL_render.h"
#include "Renderer.h"
#include "MapTile.h"
#include "MapTileEdge.h"
#include "ServiceLocator.h"
dae::MapManager::MapManager()
{
	
	r = new SDL_Rect;
}


dae::MapManager::~MapManager()
{
	delete r;
	

	
}

void dae::MapManager::LoadMap(dae::Levels Level)
{
	MapTile m;
	m_Renderer = ServiceLocator::GetRenderer();
	m_Tiles = std::vector<std::vector<MapTile>>(g_vertical_blocks, std::vector<MapTile>(g_horizontal_blocks, m));

	switch (Level)
	{
	case Levels::DEMO:
		
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
					//auto  mp = std::make_unique<MapTileEdge>(new MapTileEdge(m_Tiles[y][x], m_Tiles[y][1 + x], EdgeDir::Vertical));
					//m_TileEdges.push_back(std::make_unique<MapTileEdge>());
					m_TileEdges.push_back(std::unique_ptr<MapTileEdge>());
					m_TileEdges.at(m_TileEdges.size() - 1).reset(new MapTileEdge(m_Tiles[y][x], m_Tiles[y][1 + x], EdgeDir::Vertical));
					m_Tiles[y][x].m_RightEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
					m_Tiles[y][1 + x].m_LeftEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
				}
				if (y < g_vertical_map_blocks - 1)
				{
					//auto  mp = std::make_unique<MapTileEdge>(new MapTileEdge(m_Tiles[y][x], m_Tiles[1 + y][x], EdgeDir::Horizontal));
					m_TileEdges.push_back(std::unique_ptr<MapTileEdge>());
					m_TileEdges.at(m_TileEdges.size() - 1).reset(new MapTileEdge(m_Tiles[y][x], m_Tiles[1 + y][x], EdgeDir::Horizontal));
					m_Tiles[y][x].m_DownEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
					m_Tiles[1 + y][x].m_UpEdge = m_TileEdges.at(m_TileEdges.size() - 1).get();
					
				}

			}
		}

		break;
	case Levels::Level1:
		break; 
	case Levels::Level2:
		break;

	}
}

dae::MapTileEdge*  dae::MapManager::GetMapTileEdgeFromCoord(Vec2 pos, dae::Orientation orientation)
{
	// TODO: insert return statement here
	float x = pos.x; 
	float y = pos.y; 

	
	y -= (g_blocksize * g_empty_top_rows);
	y /= g_blocksize;
	x /= g_blocksize;
	if (x < 0 || (int)x >= g_horizontal_blocks)
	{
		return nullptr;
	}
	else if (y < 0 || (int)y >= g_vertical_map_blocks)
	{
		return nullptr;
	}
	
	MapTile &mt = m_Tiles[(unsigned int)round(y)][(unsigned int)round(x)];


	switch (orientation)
	{
	case::dae::Orientation::Bottom: 
		return mt.m_DownEdge;
		break;
	case::dae::Orientation::Top:
		return mt.m_DownEdge;
		break;
	case::dae::Orientation::Left:
		return mt.m_RightEdge;
		break;
	case::dae::Orientation::Right:
		return mt.m_RightEdge;
		break;
	}
	return nullptr;


	
	
}


dae::MapTile & dae::MapManager::GetTileFromCoord(int x, int y)
{
	//relationship between location in memory and location on map allows this 
	y -= (g_blocksize * g_empty_top_rows); 
	y /= g_blocksize; 
	x /= g_blocksize; 
	if (x < 0 || x >= g_horizontal_blocks)
	{
		return m_Tiles[0][0];
	}
	if (y < 0 || y >= g_vertical_map_blocks)
	{
		
		return m_Tiles[0][0];
	}
	return m_Tiles[y][x];


}
void dae::MapManager::Render() const
{
	
	SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 150, 150, 200, 255);
	for (int y = 0; y < g_vertical_map_blocks; y++)
	{
		for (int x = 0; x < g_horizontal_blocks; x++)
		{
			auto pos = m_Tiles[y][x].m_Position.GetPosition(); 
			//SDL_RenderDrawLine(renderer.GetSDLRenderer(), (int)pos.x, (int)pos.y, (int)pos.x + 20, (int)pos.y + 20);
			//SDL_RenderDrawLine(renderer.GetSDLRenderer(), 0,0, (int)pos.x, (int)pos.y);
		
				if (!m_Tiles[y][x].m_IsTraversible)
				{
					SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 15, (Uint8)(150 ), (Uint8) 16, 255);
				}
				else
				{
					SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), (Uint8)(150 ), (Uint8)(( 0)), (Uint8)15, 255);
				}


				
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
	
		auto redmod = ((int)edge->IsPassable * 100);
		//if (edge->m_Dir == Horizontal)
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), (Uint8)(15 * redmod), (Uint8)(( 200 -redmod)), (Uint8) 60, 255);
		//else
		//	SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), (Uint8)(15 * redmod), (Uint8)((60)), (Uint8) (240 - redmod), 255);

		p1x = edge->ReturnFirstPoint().x;
		p1y = edge->ReturnFirstPoint().y;
		p2x = edge->ReturnSecondPoint().x;
		p2y = edge->ReturnSecondPoint().y;
		SDL_RenderDrawLine(m_Renderer->GetSDLRenderer(), (int)(p1x), (int)(p1y), (int)p2x, (int)p2y);
		

	}

}
