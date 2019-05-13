#include "MiniginPCH.h"
#include "AiStates.h"
#include "ServiceLocator.h"
#include "PositionComponent.h"
std::pair<bool, dae::BaseAiState*> dae::MovingAiState::Update(float dt)
{
	//Test if destination is reaached 
	auto pos = m_Owner.m_PositionComponent.GetPosition();
	auto distancevec = Vec2(m_Destination.x - pos.x, m_Destination.y - pos.y); 
	float distance = sqrt(distancevec.x * distancevec.x + distancevec.y * distancevec.y); 
	if (distance < 0.001)
	{
		auto stopCommand = ServiceLocator::GetCommandFactory()->AiStop();
		stopCommand(&m_Owner.m_MoveComponent, &m_Owner.m_AnimationComponent);
		m_HasReachedDestination = true;
		m_ElapsedTime = 0;
	}
	m_ElapsedTime += dt;
	if (m_ElapsedTime > 1)
	{
//		m_ElapsedTime = 0;
		//m_HasReachedDestination = true; 
	}
	if (m_HasReachedDestination)
	{
		//Calculate new destination or  go to idle 
		m_HasReachedDestination = false; 
		
		auto r = ServiceLocator::GetAiManager()->CalculateNewDestination(Vec2(pos.x, pos.y)); 
		if (r.first)
			m_Destination = r.second;
		else 
			return  { false,  nullptr };
		auto dist = Vec2(r.second.x - pos.x, r.second.y - pos.y); 
		if (dist.x < 0.1 &&   dist.y < 0.1) 
			return  { false,  nullptr };
		dae::Orientation  dir{};
		if (dist.x > 1)
			dir = Right; 
		if (dist.x < -1)
			dir = Left; 
		if (dist.y > 1)
			dir = Bottom;  
		if (dist.y < -1)
			dir = Top;

		auto moveCommand = ServiceLocator::GetCommandFactory()->AiMovement(dir); 
		moveCommand(&m_Owner.m_MoveComponent, &m_Owner.m_AnimationComponent); 
	}

	return  { false,  nullptr }; 

}
