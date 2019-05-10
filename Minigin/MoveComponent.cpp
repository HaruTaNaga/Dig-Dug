#pragma once
#include "MiniginPCH.h"
#include "MoveComponent.h"
#include "ComponentsH.h"
#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <string>
#include "MapManager.h"
#include "MapTile.h"

void dae::MoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto currPos = m_PositionComponent.GetPosition();
	AdjustedVelocity = mVelocity; 
	CalculateVelocity(currPos.y, AdjustedVelocity, yAlligned, mVelocity.x, false);
	CalculateVelocity(currPos.x, AdjustedVelocity, xAlligned, mVelocity.y, true);

	//Allign sprite 
	AllignSprite(yAlligned, mVelocity.x, currPos.y);
	AllignSprite(xAlligned, mVelocity.y, currPos.x);


	auto newx = currPos.x + (deltaTime * AdjustedVelocity.x);
	auto newy = currPos.y + (deltaTime * AdjustedVelocity.y);
	//Collision
	m_PositionComponent.SetPosition(newx, newy, currPos.z);
	bool isCol = m_PhysicsComponent.IsColliding(dae::Vec2(newx, newy));
	if (isCol)
		m_PositionComponent.SetPosition(currPos.x, currPos.y, currPos.z);
	
}

void dae::MoveComponent::CalculateVelocity(const float currPos, glm::vec2 & newvel, bool & IsAliigned,  const float vel, const bool isY)
{
	if (vel != 0)
	{
		// check allignment 
		auto modulo = fmod(currPos, 32);
		if (modulo > 16)
			modulo = 32 - modulo;
		if (modulo > 2.0f) { //if distance position to grid point is larger then 2        
			IsAliigned = false;
			double intpart;
			auto fracpart = modf(currPos / 32, &intpart);
			if (fracpart < 0.5) { //adjust x or y
				if (isY) { newvel.x = -g_runspeed; newvel.y = 0; } 
				else { newvel.y = -g_runspeed; newvel.x = 0; }
			}
			else {
				if (isY) { newvel.x = g_runspeed; newvel.y = 0; }
				else { newvel.y = g_runspeed; newvel.x = 0; }
			}
		}

	}
}
void dae::MoveComponent::AllignSprite(bool isAlligned, float v  , float & position)
{
	if ((isAlligned && v != 0) || m_AllignmentTriggerCtr > 20)
	{
		m_AllignmentTriggerCtr = 0;
		auto mod = (float)fmod((position), 32.0);
		if (mod < 3)
			position -= (float)fmod((position), 32.0);
		if (mod > 29)
			position += 32 - (float)fmod((position), 32.0);
		 xAlligned = true;
		 yAlligned = true;
	}
	else
		m_AllignmentTriggerCtr++;
}
