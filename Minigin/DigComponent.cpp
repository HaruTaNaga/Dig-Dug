#pragma once
#include "MiniginPCH.h"
#include "DigComponent.h"

void dae::DigComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto orientation = m_OrientationComp.m_Orientation;
	auto pos = m_PositionComp.GetPosition();
	auto & m = m_MapMgr->GetTileFromCoord((int)roundf(pos.x + 16), (int)roundf(pos.y + 16));
	m.m_IsTraversible = true;
	auto vel = m_MoveComp.GetVelocity();
	if (vel == glm::vec2(0, 0))
		return;

//if (m_MoveComp.xAlligned != true || m_MoveComp.yAlligned != true)
//return;
	auto edge = MapManager::GetInstance().GetMapTileEdgeFromCoord(dae::Vec2((int)roundf(pos.x  + 16), (int)roundf(pos.y  + 16)), orientation);
	if (edge != nullptr)
		edge->IsPassable = true;

	
}
