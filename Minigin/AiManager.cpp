#include "MiniginPCH.h"
#include "AiManager.h"
#include "ServiceLocator.h"
#include  <random>
#include "PositionComponent.h"
#include "MapTile.h"
#include <time.h>
dae::AiManager::AiManager()
{

}
static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long xorshf96(void) {          //period 2^96-1
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}
std::pair<bool,dae::Vec2> dae::AiManager::CalculateNewDestination(Vec2 enemyPos)
{
	auto const MapManager = ServiceLocator::GetMapManager(); 
	auto const CurrentTile = MapManager->GetTileFromCoord((int)enemyPos.x, (int)enemyPos.y);
	
	//Take random direction 
	for (int i = 0; i < 15; i++)
	{
		std::srand((UINT32)time(NULL));
		dae::Orientation dir = static_cast<Orientation>(xorshf96() % 4);
 		auto p = CheckDir(CurrentTile, dir);
		if (p.first)
			return p;
	}

	
	return { false, Vec2(enemyPos.x, enemyPos.y) };

}

std::pair<bool, dae::Orientation> dae::AiManager::CalculateNewDirection(Vec2 enemyPos)
{
	auto const MapManager = ServiceLocator::GetMapManager();
	auto const CurrentTile = MapManager->GetTileFromCoord((int)enemyPos.x, (int)enemyPos.y);

	//Take random direction 
	dae::Orientation dir{}; 
	for (int i = 0; i < 5; i++)
	{
		dir = static_cast<Orientation>(rand() % 4);
		auto p = CheckDir(CurrentTile, dir);
		if (p.first)
			return { true, dir };
	}


	return { false, dir };

}
dae::Vec2 dae::AiManager::CalculateGhostDestination(Vec2 enemyPos)
{
	//Calculate random  available  tile to move  to 

	auto const MapManager = ServiceLocator::GetMapManager();
	auto const CurrentTile = MapManager->GetTileFromCoord((int)enemyPos.x, (int)enemyPos.y);
	std::vector<dae::MapTile *> PossibleTiles{};

	for (int r = -4; r < 4; r++)
		for (int c = -4; c < 4; c++)
		{
			if (abs(r) <= 1 || abs(c) <= 1)
				continue; 

			auto newpos = Vec2(enemyPos.x + (r * 32), enemyPos.y + (c * 32)); 
			auto const pair = MapManager->TryGetTileFromCoord(newpos);
			if (pair.first && pair.second->m_IsTraversible)
				PossibleTiles.push_back(pair.second);
		}

	if (PossibleTiles.size() == 0)
		return  Vec2(enemyPos.x, enemyPos.y);
	auto tile= PossibleTiles[PossibleTiles.size() - (1 + (rand() % PossibleTiles.size()))];
	auto tilepos = tile->m_Position.GetPosition(); 

  		return Vec2(tilepos.x,tilepos.y);

}
std::pair<bool,dae::Vec2> dae::AiManager::CheckDir( dae::MapTile const  &  m_Tile, dae::Orientation dir) const
{
	

	switch (dir)
	{
	case Orientation::Bottom:
		if (m_Tile.m_DownEdge != nullptr && m_Tile.m_DownEdge->IsPassable)
		{
			 auto const TilePos = m_Tile.m_DownEdge->m_MapTile2.m_Position.GetPosition();
			return {true, Vec2(TilePos.x, TilePos.y) };
		}
		break;
	case Orientation::Top:
		if (m_Tile.m_UpEdge != nullptr && m_Tile.m_UpEdge->IsPassable)
		{
			 auto const  TilePos = m_Tile.m_UpEdge->m_MapTile1.m_Position.GetPosition();
			return { true, Vec2(TilePos.x, TilePos.y) };
		}
		break;
	case Orientation::Left:
		if (m_Tile.m_LeftEdge != nullptr && m_Tile.m_LeftEdge->IsPassable)
		{
			 auto const  TilePos = m_Tile.m_LeftEdge->m_MapTile1.m_Position.GetPosition();
 			return { true, Vec2(TilePos.x, TilePos.y) };
		}
		break;
	case  Orientation::Right:
		if (m_Tile.m_RightEdge != nullptr && m_Tile.m_RightEdge->IsPassable)
		{
			 auto const  TilePos = m_Tile.m_RightEdge->m_MapTile2.m_Position.GetPosition();
			return { true, Vec2(TilePos.x, TilePos.y) };
		}
		break;
	};

	return { false,Vec2(0, 0) };
}
