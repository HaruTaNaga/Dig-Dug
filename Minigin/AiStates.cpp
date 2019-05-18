#include "MiniginPCH.h"
#include "AiStates.h"
#include "ServiceLocator.h"
#include "PositionComponent.h"
#include <time.h>
#include "StateComponent.h"
std::pair<bool, dae::BaseAiState*> dae::MovingAiState::Update(float dt)
{
	//Test if destination is reaached 
	auto pos = m_Owner.m_PositionComponent.GetPosition();
	auto distancevec = Vec2(m_Destination.x - pos.x, m_Destination.y - pos.y); 
	float distance = sqrt(distancevec.x * distancevec.x + distancevec.y * distancevec.y); 
	
	m_ElapsedTime += dt;
	/*if (m_ElapsedTime >= 0.512)
	{
		m_ElapsedTime = 0;
		m_HasReachedDestination = true; 
		ServiceLocator::GetCommandFactory()->AiStop()(&m_Owner.m_PositionComponent, &m_Owner.m_MoveComponent, &m_Owner.m_AnimationComponent);
		m_HasReachedDestination = true;
		m_ElapsedTime = 0;
		return { true, new IdleAiState(m_Owner) };
	}*/
	if (m_HasReachedDestination )
	{
		auto currentstate = m_Owner.m_StateComponent.GetState(); 
		if (dynamic_cast<InflationState *>(currentstate) != nullptr || dynamic_cast<EnemyDeathState *>(currentstate) != nullptr)
			return  { false, nullptr };
		//Calculate new destination or  go to idle 
		m_HasReachedDestination = false; 
		
		auto r = ServiceLocator::GetAiManager()->CalculateNewDestination(Vec2(pos.x, pos.y)); 
		if (r.first)
			m_Destination = r.second;
		else 
			return  { false,  nullptr };
		auto dist = Vec2(r.second.x - pos.x, r.second.y - pos.y); 
		if (abs(dist.x) < 0.1 &&   abs(dist.y) < 0.1) 
			return  { false,  nullptr };
		dae::Orientation  dir{};
		if (dist.x > 1 && abs(dist.y) < 1)
			dir = Right;
		else if (dist.x < -1 && abs(dist.y) < 1)
			dir = Left;
		else if (dist.y > 1 && abs(dist.x) < 1)
			dir = Bottom;
		else if (dist.y < -1 && abs(dist.x) < 1)
			dir = Top;
		
			
		ServiceLocator::GetCommandFactory()->AiMovement(dir)
			(&m_Owner.m_MoveComponent, &m_Owner.m_AnimationComponent);

	}
	if (distance < 1 )
	{
		ServiceLocator::GetCommandFactory()->AiStop()(&m_Owner.m_PositionComponent, &m_Owner.m_MoveComponent, &m_Owner.m_AnimationComponent);
			m_HasReachedDestination = true;
			m_ElapsedTime = 0;
			return { true, new IdleAiState(m_Owner) };
	}
	return  { false,  nullptr }; 

}

std::pair<bool, dae::BaseAiState*> dae::IdleAiState::Update(float dt)
{

	m_ElapsedTime += dt;
	if (m_ElapsedTime > 0.4 && m_Owner.m_AnimationComponent.m_ActiveAnimationId <= 2)
	{
		m_ElapsedTime = 0;
		//std::srand((UINT32)time(NULL));
		if (rand() % (int)(1 / m_ChanceToGhost) == 0)
		{
			ServiceLocator::GetCommandFactory()->AiGhost() (&m_Owner.m_AnimationComponent);
			return { true, new GhostAiState(m_Owner) };
		}
			
		if (rand() % (int)(1 / m_ChanceToMove) == 0)
			return { true, new MovingAiState(m_Owner) };

	}

	return  { false, nullptr };

};

std::pair<bool, dae::BaseAiState*> dae::GhostAiState::Update(float )
{
	return  { false, nullptr };
}
