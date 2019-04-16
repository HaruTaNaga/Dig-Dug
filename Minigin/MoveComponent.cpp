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

	//bool AdjustingY = false; 
	//bool AdjustingX = false;
	glm::vec2 AdjustedVelocity = mVelocity; 
	CalculateVelocity(currPos.y, AdjustedVelocity, yAlligned, mVelocity.x, false);
	CalculateVelocity(currPos.x, AdjustedVelocity, xAlligned, mVelocity.y, true);

	//Allign sprite 
	AllignSprite(yAlligned, mVelocity.x, currPos.y);
	AllignSprite(xAlligned, mVelocity.y, currPos.x);

	//Check Boundaries
	auto newx = currPos.x + (deltaTime * AdjustedVelocity.x);
	auto newy = currPos.y + (deltaTime * AdjustedVelocity.y);

	if (m_PhysicsComponent.IsOutOfMapBounds(newx, newy))
		return; 
	m_PositionComponent.SetPosition(newx,newy, currPos.z);

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


/*
if (yAlligned && mVelocity.x != 0)
{
	auto mod = (float)fmod((currPos.y), 32.0);
	if (mod < 2)
		currPos.y -= (float)fmod((currPos.y), 32.0);
	if (mod > 29)
		currPos.y += 32 - (float)fmod((currPos.y), 32.0);

}
if (xAlligned && mVelocity.y != 0)
{
	auto mod = (float)fmod((currPos.x), 32.0);
	if (mod < 3)
		currPos.x -= (float)fmod((currPos.x), 32.0);
	if (mod > 29)
		currPos.x += 32 - (float)fmod((currPos.x), 32.0);
}
*/
//__________//

	/*
	if (mVelocity.x != 0)
	{
		// check allignment
		auto modulo = fmod(currPos.y, 32);
		if (modulo > 16)
			modulo = 32 - modulo;
		if (modulo > 2.f) {
			yAlligned = false;
			double intpart;
			auto fracpart = modf(currPos.y / 32, &intpart);
			if (fracpart < 0.5)	{
				AdjustingY = true;
				AdjustedVelocity.y = -g_runspeed;
				AdjustedVelocity.x = 0; }
			else {
				AdjustedVelocity.y = g_runspeed;
				AdjustedVelocity.x = 0; }

		}

	}

	//Check if able to turn
	if (mVelocity.y != 0)
	{
		// check allignment
		auto modulo = fmod(currPos.x, 32);
		if (modulo > 16)
			modulo = 32 - modulo;
		if (modulo > 2.0f) {
			xAlligned = false;
			double intpart;
			auto fracpart = modf(currPos.x / 32, &intpart);
			if (fracpart < 0.5) {
				AdjustingX = true;
				AdjustedVelocity.x = -g_runspeed;
				AdjustedVelocity.y = 0; }
			else {
				AdjustedVelocity.x = g_runspeed;
				AdjustedVelocity.y = 0; }
		}

	}
	*/

	/*
	auto & m = MapManager::GetInstance().GetTileFromCoord((int)roundf(newx + 16), (int)roundf(newy + 16));

	m.m_IsTraversible = true;

		//c->isTraversible = false;

	dae::Orientation orient = Orientation::Right ;
	if (AdjustedVelocity.x > 0)
		orient = Orientation::Right;
	if (AdjustedVelocity.x < 0)
		orient = Orientation::Left;
	if (AdjustedVelocity.y > 0)
		orient = Orientation::Bottom;
	if (AdjustedVelocity.y < 0)
		orient = Orientation::Top;
	if (AdjustedVelocity == glm::vec2(0, 0))
		return;
	auto edge = MapManager::GetInstance().GetMapTileEdgeFromCoord(dae::Vec2((int)roundf(newx), (int)roundf(newy)), orient);
	if (edge != nullptr)
		edge->IsPassable = true;*/

		//mVelocity = AdjustedVelocity;
		/*
		auto xoffset = g_width - g_blocksize;
		auto ytopoffset = (g_blocksize * (g_empty_top_rows-1));
		auto ybotoffset = g_height - (g_blocksize + g_blocksize * g_empty_bottom_rows);
		if (newx > xoffset
			|| newx < 0)
			return;
		if ( newy < ytopoffset
			|| newy > ybotoffset)
			return;
			*/

			/*
			if (mVelocity.x != 0)
			{
				// check allignment
				auto modulo = fmod(currPos.y, 32);
				if (modulo > 16)
					modulo = 32 - modulo;
				if (modulo > 2.f) {
					yAlligned = false;
					double intpart;
					auto fracpart = modf(currPos.y / 32, &intpart);
					if (fracpart < 0.5) {

						AdjustedVelocity.y = -g_runspeed;
						AdjustedVelocity.x = 0;
					}
					else {
						AdjustedVelocity.y = g_runspeed;
						AdjustedVelocity.x = 0;
					}

				}

			}

			//Check if able to turn
			if (mVelocity.y != 0)
			{
				// check allignment
				auto modulo = fmod(currPos.x, 32);
				if (modulo > 16)
					modulo = 32 - modulo;
				if (modulo > 2.0f) {
					xAlligned = false;
					double intpart;
					auto fracpart = modf(currPos.x / 32, &intpart);
					if (fracpart < 0.5) {

						AdjustedVelocity.x = -g_runspeed;
						AdjustedVelocity.y = 0;
					}
					else {
						AdjustedVelocity.x = g_runspeed;
						AdjustedVelocity.y = 0;
					}
				}

			}*/