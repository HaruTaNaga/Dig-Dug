#include "MiniginPCH.h"
#include "MapManager.h"
#include "SDL_render.h"
#include "Renderer.h"
#include "MapTile.h"
#include "MapTileEdge.h"
dae::MapManager::MapManager()
{
}


dae::MapManager::~MapManager()
{
}

void dae::MapManager::LoadMap(dae::Levels Level)
{
	MapTile m;

	//m_Tiles = std::vector<std::vector<MapTile>>(g_vertical_blocks, std::vector<MapTile>(g_horizontal_blocks, m));
	m_Tiles = std::vector<std::vector<MapTile>>(g_vertical_blocks, std::vector<MapTile>(g_horizontal_blocks, m));
	//m_TileEdges = std::vector<MapTileEdge *>(g_vertical_blocks * g_horizontal_blocks * 2 - g_vertical_blocks - g_horizontal_blocks);

	
	switch (Level)
	{
	case Levels::DEMO:
		
		for (int y = 0; y < g_vertical_map_blocks; y++)
		{
			for (int x = 0; x < g_horizontal_blocks; x++)
			{
				//m_Tiles[y][x].m_Position.SetPosition(x * 32.0f, (32.0f * 3) + (32 * y),0);
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
					MapTileEdge * mp = new MapTileEdge(m_Tiles[y][x], m_Tiles[y][1 + x], EdgeDir::Vertical);
					m_TileEdges.push_back(mp);
					m_Tiles[y][x].m_RightEdge = mp;
					m_Tiles[y][1 + x].m_LeftEdge = mp;
				}
				if (y < g_vertical_map_blocks - 1)
				{
					MapTileEdge * mp = new MapTileEdge(m_Tiles[y][x], m_Tiles[1 + y][x], EdgeDir::Horizontal);
					m_TileEdges.push_back(mp);
					m_Tiles[y][x].m_DownEdge = mp;
					m_Tiles[1 + y][x].m_UpEdge = mp;
					//m_TileEdges[EdgeCtr++].MapTile1 = m_Tiles[y][x];
					//m_TileEdges[EdgeCtr++].MapTile2 = m_Tiles[y+1][x];
				}



			}
		}
		for (int y = 0; y < g_vertical_map_blocks; y++)
		{
			for (int x = 0; x < g_vertical_blocks * 2 - 1; x++)
			{
				//m_Tiles[y][x].m_Position.SetPosition(x * 32.0f, (32.0f * 3) + (32 * y),0);
				//m_Tiles[y][x].SetPosition(x * 32, (32 * 3) + (32 * y));
				//m_TileEdges[x + (g_vertical_blocks * 2 - 1 * y)].MapTile1 = m_Tiles[y][x];

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

	switch (orientation)
	{
	case::dae::Orientation::Bottom:

		//	y+= 0.1f;
		break;
	case::dae::Orientation::Top:
		if  (y >0)
		//y -= 0.1f; 
		break;
	case::dae::Orientation::Left:
		if (x > 0)
		//x -= 0.1f; 
		break;
	case::dae::Orientation::Right:

		//	x += 0.1f;
		break;
	}
	MapTile * mt;  
	y -= (g_blocksize * g_empty_top_rows);
	y /= g_blocksize;
	x /= g_blocksize;
	if (x < 0 || (int)x >= g_horizontal_blocks)
	{

		return nullptr;
	}
	else if (y < 0 || (int)y >= g_vertical_map_blocks)
	{
		//TODO ERROR 
		return nullptr;
	}
	else
		mt = &m_Tiles[(unsigned int)y][(unsigned int)x];


	switch (orientation)
	{
	case::dae::Orientation::Bottom: 
		return mt->m_DownEdge;
		break;
	case::dae::Orientation::Top:
		return mt->m_DownEdge;
		break;
	case::dae::Orientation::Left:
		return mt->m_RightEdge;
		break;
	case::dae::Orientation::Right:
		return mt->m_RightEdge;
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
		//TODO ERROR 
		return m_Tiles[0][0];
	}
	return m_Tiles[y][x];

}
void dae::MapManager::Render() const
{
	auto renderer = m_ServiceLocator.GetRenderer();
	SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 150, 150, 200, 255);
	for (int y = 0; y < g_vertical_map_blocks; y++)
	{
		for (int x = 0; x < g_horizontal_blocks; x++)
		{
			auto pos = m_Tiles[y][x].m_Position.GetPosition(); 
			//SDL_RenderDrawLine(renderer.GetSDLRenderer(), (int)pos.x, (int)pos.y, (int)pos.x + 20, (int)pos.y + 20);
			//SDL_RenderDrawLine(renderer.GetSDLRenderer(), 0,0, (int)pos.x, (int)pos.y);
		
				if (m_Tiles[y][x].m_IsTraversible)
				{
					SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 150, (Uint8)(150 ), (Uint8) 160, 255);
				}
				else
				{
					SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), (Uint8)(150 ), (Uint8)(( 0)), (Uint8)15, 255);
				}


				SDL_Rect * r = new SDL_Rect; 
				r->x = (int)pos.x - 4 + 16;
				r->y = (int)pos.y - 4 + 16; 
				r->h = 8; 
				r->w = 8;

	
				SDL_RenderDrawRect(renderer->GetSDLRenderer(), r);

		}
	}
	int counter = 0;
	UNREFERENCED_PARAMETER(counter);
	for (auto edge : m_TileEdges)
	{
		auto m1 = edge->m_MapTile1; 
		auto m2 = edge->m_MapTile2; 
		auto from = m1.m_Position.GetPosition(); 
		auto to = m2.m_Position.GetPosition(); 
		//float distVecx = (to.x - from.x) * 0.5f;
		//float distVecy = (to.y - from.y) * 0.5f;
		auto p1x = 0.0f; 
		auto p1y = 0.0f; 

		auto p2x = 0.0f; 
		auto p2y = 0.0f; 
		//float distVecx2 = (to.x - from.x) * 0.15f;
	//	if (from.y < 96 || to.y < 96)
	//		to.y += 15; 
		//float distVecy2 = (to.y - from.y) * 0.15f;
		//if (counter++ < 121 || counter > 123) {}
		//else
		auto redmod = ((int)edge->IsPassable * 100);
		if (edge->m_Dir == Horizontal)
		{
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), (Uint8)(15 * redmod), (Uint8)(( 200)), (Uint8) 60, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), (Uint8)(15 * redmod), (Uint8)((60)), (Uint8) 240, 255);
		}
		//auto pos = edge->ReturnFirstPoint(); 
		//auto pos2 = edge->ReturnSecondPoint(); 
		p1x = edge->ReturnFirstPoint().x;
		p1y = edge->ReturnFirstPoint().y;
		p2x = edge->ReturnSecondPoint().x;
		p2y = edge->ReturnSecondPoint().y;
		SDL_RenderDrawLine(renderer->GetSDLRenderer(), (int)(p1x), (int)(p1y), (int)p2x, (int)p2y);
		//SDL_RenderDrawLine(renderer.GetSDLRenderer(), (int)(from.x), (int)(from.y), (int)to.x, (int)to.y);
		//SDL_RenderDrawLine(renderer.GetSDLRenderer(), (Uint8)(from.x), (Uint8)(from.y), (Uint8)to.x, (Uint8)to.y);

	}
		//SDL_RenderDrawLine(renderer.GetSDLRenderer(), *tile)
//	SDL_RenderDrawLine(renderer.GetSDLRenderer(), 0, 0, 10, 100);
//	SDL_RenderDrawLine(renderer.GetSDLRenderer(), 0, 0, 100, 100);
	//SDL_RenderDrawLine(renderer.GetSDLRenderer(), 0, 0, g_width, g_height);
}
