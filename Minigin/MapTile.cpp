#include "MiniginPCH.h"
#include "MapTile.h"


dae::MapTile::MapTile(Transform pos)
{
	auto start = pos; 
	auto end = pos; 
	end.SetPosition(glm::vec3(start.GetPosition().x + 32, start.GetPosition().y, start.GetPosition().z));
	m_Connections[0] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x - 32, start.GetPosition().y, start.GetPosition().z));
	m_Connections[1] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x , start.GetPosition().y -32, start.GetPosition().z));
    m_Connections[2] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x, start.GetPosition().y + 32, start.GetPosition().z));
	m_Connections[3] = new Connection(start, end);


}


dae::MapTile::~MapTile()
{
}

void dae::MapTile::SetPosition(int x, int y)
{
	m_Position.SetPosition(glm::vec3(x, y, 0));
	auto start = m_Position;
	auto end = start;
	end.SetPosition(glm::vec3(start.GetPosition().x + 32, start.GetPosition().y, start.GetPosition().z));
	m_Connections[0] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x - 32, start.GetPosition().y, start.GetPosition().z));
	m_Connections[1] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x, start.GetPosition().y - 32, start.GetPosition().z));
	m_Connections[2] = new Connection(start, end);
	end.SetPosition(glm::vec3(start.GetPosition().x, start.GetPosition().y + 32, start.GetPosition().z));
	m_Connections[3] = new Connection(start, end);

}