#pragma once
#include "Transform.h"
#include "Texture2D.h"


namespace dae {

	
	
	
	struct Connection {

		Connection() {};
		Connection(const Transform startpos, const Transform endpos) :
			startPosition(startpos),
			endPosition(endpos) {}; 
		Transform startPosition; 
		Transform endPosition; 
		bool isTraversible = false;
	};
	class MapTileEdge;
	class MapTile
	{
	public:
		MapTile() {};
		MapTile(Transform pos) ;
		~MapTile();

		bool isEmpty = false; 
		void SetPosition(int x, int y);
		Transform m_Position; 
		Connection * m_Connections[4];
		bool m_IsTraversible = false;
		MapTileEdge * m_UpEdge;
		MapTileEdge * m_DownEdge;
		MapTileEdge * m_LeftEdge;
		MapTileEdge * m_RightEdge;


	};
}
