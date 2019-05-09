#include "MiniginPCH.h"
#include "Map.h"

dae::Map::Map()
{

}

dae::Map::~Map()
{

}

void dae::Map::LoadMap(dae::Levels Level)
{
	MapTile m{ };
	switch (Level)
	{
	case Levels::DEMO:
	

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
		break;
	case Levels::Level2:
		break;

	}
}

dae::MapTileEdge * dae::Map::GetMapTileEdgeFromCoord(Vec2 pos, dae::Orientation orientation)
{
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

dae::MapTile & dae::Map::GetTileFromCoord(int x, int y)
{

	//relationship between location in memory and location on map
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
