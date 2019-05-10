#include "MiniginPCH.h"
#include "PhysicsComponent.h"

#include "ComponentsH.h"
#include  "glm\vec3.hpp"


dae::PhysicsComponent::~PhysicsComponent()
{
}

void dae::PhysicsComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

bool dae::PhysicsComponent::IsOutOfMapBounds(const float x, const float y)
{
	auto xoffset = g_width - g_blocksize;
	auto ytopoffset = (g_blocksize * (g_empty_top_rows - 1));
	auto ybotoffset = g_height - (g_blocksize + g_blocksize * g_empty_bottom_rows);
	if (x > xoffset || x < 0 || y < ytopoffset || y > ybotoffset)
		return true;

	return false;
}

bool dae::PhysicsComponent::IsColliding(dae::Vec2 pos)
{
	//auto pos = posComp.GetPosition();
	auto c = m_CollisionComponent.CheckCollision(pos); 
	auto b = (IsOutOfMapBounds((float)pos.x, (float)pos.y));
	auto r = c || b;
	return r ;
}
