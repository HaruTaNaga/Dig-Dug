#pragma once
#include "MapTile.h"
namespace dae {
	enum EdgeDir {
		Horizontal, 
		Vertical,  
		NotSpecified 
	};

	
	class MapTileEdge {

	public: 
		MapTileEdge() = delete; 
		MapTileEdge(MapTile & mp1, MapTile & mp2, EdgeDir dir) : m_MapTile1(mp1), m_MapTile2(mp2), m_Dir(dir)
		{
			if (m_Dir == Horizontal)
			{
				m_Positions.Pos1 = Vec2(m_MapTile2.m_Position.GetPosition().x, m_MapTile2.m_Position.GetPosition().y);
				m_Positions.Pos2 = Vec2(m_MapTile2.m_Position.GetPosition().x + 32, m_MapTile2.m_Position.GetPosition().y  );
			}
			else if (m_Dir == Vertical)
			{
				m_Positions.Pos1 = Vec2(m_MapTile2.m_Position.GetPosition().x, m_MapTile2.m_Position.GetPosition().y);
				m_Positions.Pos2 = Vec2(m_MapTile2.m_Position.GetPosition().x , m_MapTile2.m_Position.GetPosition().y + 32);
			}


		};
		MapTile & m_MapTile1; 
		MapTile & m_MapTile2; 
		EdgeDir m_Dir;
		Line m_Positions;
		bool IsPassable = false; 
		dae::Vec2 ReturnFirstPoint()
		{
			return m_Positions.Pos1;
		}
		dae::Vec2 ReturnSecondPoint()
		{
			return m_Positions.Pos2;
		}
	};
}