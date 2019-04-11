#include "MiniginPCH.h"
#include "PhysicsComponent.h"




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
	if (x > xoffset || x < 0)
		return true;
	if (y < ytopoffset || y > ybotoffset)
		return true;
	return false;
}
