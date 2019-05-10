#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
dae::GameObject::GameObject()
{


}
dae::GameObject::~GameObject() {
	
};

void dae::GameObject::Update(const float deltaTime)
{
	for (auto comp : mComponentvec)
	{
		comp->Update(deltaTime);
	}

}
