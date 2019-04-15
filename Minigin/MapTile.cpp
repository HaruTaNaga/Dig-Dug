#include "MiniginPCH.h"
#include "MapTile.h"


dae::MapTile::MapTile(Transform post)
{
	auto pos = post.GetPosition(); 
	m_Position.SetPosition(glm::vec3(pos.x,pos.y,pos.z));

}


dae::MapTile::~MapTile()
{
}

void dae::MapTile::SetPosition(int x, int y)
{

	m_Position.SetPosition(glm::vec3(x, y, 0));
	
}