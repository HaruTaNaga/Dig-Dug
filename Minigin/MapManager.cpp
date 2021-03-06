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
	


}


dae::MapManager::~MapManager()
{
	
	
}

void dae::MapManager::LoadMap(dae::Levels Level)
{

	m_Maps.push_back(std::unique_ptr<Map>(new Map())); 
	m_ActiveLevelid = (int)m_Maps.size() - 1; 
	m_Maps[m_ActiveLevelid]->LoadMap(Level); 
}

dae::MapTile & dae::MapManager::GetTileFromCoord(int x, int y)
{

	return m_Maps[m_ActiveLevelid]->GetTileFromCoord(x, y); 
}
std::pair<bool, dae::MapTile *>  dae::MapManager::TryGetTileFromCoord(dae::Vec2 pos)
{

	return m_Maps[m_ActiveLevelid]->TryGetTileFromCoord(pos);
}
void dae::MapManager::Render() const noexcept
{
	m_Maps[m_ActiveLevelid]->Render(); 

}
void dae::MapManager::ResetActiveMap()
{

		m_Maps[m_ActiveLevelid]->ResetMap(static_cast<Levels>(m_ActiveLevelid));


	
}

