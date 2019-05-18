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
	//auto const PlayerPos = m_PlayerPosComp.GetPosition(); 
	//auto const PlayerTile = MapManager->GetTileFromCoord(PlayerPos.x, PlayerPos.y); 
	//auto const DistanceVecX = PlayerPos.x - enemyPos.x; 
	//auto const DistanceVecY = PlayerPos.y - enemyPos.y;
	//Calc player  direction 
	/*
	if (abs(DistanceVecX) > abs(DistanceVecY))
	{
		if (DistanceVecX > 0)
		{
			//try Go Left
			if (CurrentTile.m_LeftEdge != nullptr && CurrentTile.m_LeftEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_LeftEdge->m_MapTile1.m_Position.GetPosition(); 

				return Vec2(LeftTilePos.x,LeftTilePos.y); 
			}
		}
		else
		{
			//Try go right 
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
	}
	else
	{
		if (DistanceVecY > 0)
		{
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
		else
		{
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
	}*/
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
	//auto const PlayerPos = m_PlayerPosComp.GetPosition(); 
	//auto const PlayerTile = MapManager->GetTileFromCoord(PlayerPos.x, PlayerPos.y); 
	//auto const DistanceVecX = PlayerPos.x - enemyPos.x; 
	//auto const DistanceVecY = PlayerPos.y - enemyPos.y;
	//Calc player  direction 
	/*
	if (abs(DistanceVecX) > abs(DistanceVecY))
	{
		if (DistanceVecX > 0)
		{
			//try Go Left
			if (CurrentTile.m_LeftEdge != nullptr && CurrentTile.m_LeftEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_LeftEdge->m_MapTile1.m_Position.GetPosition();

				return Vec2(LeftTilePos.x,LeftTilePos.y);
			}
		}
		else
		{
			//Try go right
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
	}
	else
	{
		if (DistanceVecY > 0)
		{
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
		else
		{
			if (CurrentTile.m_RightEdge != nullptr && CurrentTile.m_RightEdge->IsPassable)
			{
				auto LeftTilePos = CurrentTile.m_RightEdge->m_MapTile2.m_Position.GetPosition();

				return Vec2(LeftTilePos.x, LeftTilePos.y);
			}
		}
	}*/
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
std::pair<bool,dae::Vec2> dae::AiManager::CheckDir( dae::MapTile const  &  m_Tile, dae::Orientation dir) const
{
	/*
	if (m_Edge != nullptr && m_Edge->IsPassable)
	{
		auto LeftTilePos = m_Edge->m_MapTile2.m_Position.GetPosition();

		return Vec2(LeftTilePos.x, LeftTilePos.y);
	}*/


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