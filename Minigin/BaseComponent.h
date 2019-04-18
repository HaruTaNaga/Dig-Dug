#pragma once

namespace dae {

	class GameObject;
class BaseComponent
{
public: 
	BaseComponent() = default;
	BaseComponent(std::shared_ptr<GameObject> owner) {}//: m_Owner(owner) {}
	~BaseComponent() = default; 
	
	//virtual void Receive(int msg, dae::CmpType Destination ) = 0;
	virtual void Update(float )  {};
	//virtual void Initialize() = 0;
	//virtual dae::CmpType GetType() = 0;
	//void LinkToParent(GameObject & go) {m_GameObject = &go;};
protected:
	//const std::shared_ptr<GameObject> m_Owner;


private: 
	

};
}