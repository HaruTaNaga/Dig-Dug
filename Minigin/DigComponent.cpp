#pragma once
#include "MiniginPCH.h"
#include "DigComponent.h"

void dae::DigComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_MoveComp.GetVelocity() == glm::vec2(0, 0))
		return;
	

	auto orientation = m_OrientationComp.m_Orientation;
	auto pos = m_PositionComp.GetPosition();
	auto & m = m_MapMgr->GetTileFromCoord((int)roundf(pos.x + 16), (int)roundf(pos.y + 16));
	m.m_IsTraversible = true;
	if (m_LastTileTraversed == nullptr)
		m_LastTileTraversed = &m;
	else if ((m_LastTileTraversed != nullptr && m.m_Position.GetPosition() != m_LastTileTraversed->m_Position.GetPosition()) )
	{
		
		MapTileEdge * lastTraversedEdge = nullptr; 
		switch (orientation)
		{
		case Bottom:
			lastTraversedEdge = m_LastTileTraversed->m_DownEdge;
			break;
		case Left:
			lastTraversedEdge = m_LastTileTraversed->m_LeftEdge;
			break; 
		case Right:
			lastTraversedEdge = m_LastTileTraversed->m_RightEdge;
			break;
		case Top: 
			lastTraversedEdge = m_LastTileTraversed->m_UpEdge;
			break; 
		}
		if (lastTraversedEdge != nullptr)
		{
			lastTraversedEdge->IsPassable = true;
			m_LastTileTraversed = &m;
		}

		
	}
	

	
}
