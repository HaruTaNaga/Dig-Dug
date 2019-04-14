#pragma once
#include  "ComponentsH.h"
#include  "MapManager.h"
namespace  dae {

	class OrientationComponent; 
	class PositionComponent; 
	class MoveComponent; 
	class DigComponent : public BaseComponent
	{
	public: 
		DigComponent(OrientationComponent & oric ,  PositionComponent & posc,  MoveComponent & movc)
			:m_OrientationComp(oric) , m_PositionComp(posc),  m_MoveComp(movc) {
			m_MapMgr = &MapManager::GetInstance();
		
		};
		//: TextComponent(owner, texc, "", font, true) {};
		~DigComponent() {};
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::fpsComp; }
		DigComponent(const DigComponent& other) = delete;
		DigComponent(DigComponent&& other) = delete;
		DigComponent& operator=(const DigComponent& other) = delete;
		DigComponent& operator=(DigComponent&& other) = delete;
	private: 
		MapManager * m_MapMgr;
		OrientationComponent & m_OrientationComp;
		PositionComponent & m_PositionComp;
		MoveComponent & m_MoveComp;
		MapTile * m_LastTileTraversed; 

	};

}
