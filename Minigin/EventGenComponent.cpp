#include "MiniginPCH.h"
#include "EventGenComponent.h"
#include "ServiceLocator.h"

dae::EventGenComponent::EventGenComponent(GameObject & go) : m_Owner(go)
{
	
	m_EventFactory = ServiceLocator::GetEventFactory(); 
}

void dae::EventGenComponent::GenerateEmptyEvent(std::pair<std::function<void(EventArgs*)>, EventArgs*>& p)
{
	p.first = m_EventFactory->ReturnEmptyEventLamda(); 
	p.second->MComp = std::reference_wrapper<MoveComponent>(*static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>())); 
}

void dae::EventGenComponent::GenerateKeyDownEvent(std::pair<std::function<void(EventArgs*)> , EventArgs*> & pair, SDL_Keycode  key )
{
	if (key == SDLK_RIGHT || key == SDLK_LEFT ||
		key == SDLK_DOWN || key == SDLK_UP)
	{
		pair.second->MComp = std::reference_wrapper<MoveComponent>(*static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>()));
	}
	else if (key == SDLK_f)
	{
		pair.second->PComp = std::reference_wrapper<PositionComponent>(static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>())->m_PositionComponent);
	}
	pair.first = std::function<void(EventArgs*)>(m_EventFactory->ReturnEventLamdaKeyDown(key));
}

void dae::EventGenComponent::GenerateKeyUpEvent(std::pair<std::function<void(EventArgs*)>, EventArgs*> & pair)
{
	pair.second->MComp = std::reference_wrapper<MoveComponent>(*static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>()));
	pair.first = std::function<void(EventArgs*)>(m_EventFactory->ReturnEventLamdaUp());
}

void dae::EventGenComponent::Update(float )
{
}
