#include "MiniginPCH.h"
#include "EventGenComponent.h"
#include "ServiceLocator.h"
#include "ComponentsH.h"

dae::EventGenComponent::EventGenComponent(GameObject & go) : m_Owner(go)
{
	
	m_EventFactory = ServiceLocator::GetEventFactory(); 
	//auto sc = m_Owner.GetComponent<StateComponent>();

	m_StateComponent = static_cast<StateComponent *>(m_Owner.GetComponent<StateComponent>());
	m_MoveComponent = static_cast<MoveComponent *>(m_Owner.GetComponent<MoveComponent>());
	m_AnimationComponent = static_cast<AnimationComponent *>(m_Owner.GetComponent<AnimationComponent>());
	m_EventArg.reset(new EventArgs(*m_MoveComponent));
	m_FpPairEventArg = std::make_pair<std::function<void(EventArgs *)>, EventArgs * >([](EventArgs *) {}, m_EventArg.get()); 
}

void dae::EventGenComponent::GenerateEmptyEvent()
{
	m_FpPairEventArg.first = m_EventFactory->ReturnEmptyEventLamda();
	m_FpPairEventArg.second->MComp = std::reference_wrapper<MoveComponent>(*m_MoveComponent);
	NotifyStateEvent();
}

void dae::EventGenComponent::GenerateKeyDownEvent(SDL_Keycode  key )
{
	if (key == SDLK_RIGHT || key == SDLK_LEFT ||
		key == SDLK_DOWN || key == SDLK_UP)
	{
		m_FpPairEventArg.second->MComp = std::reference_wrapper<MoveComponent>(*m_MoveComponent);
		if (m_Owner.IsAnimated) m_FpPairEventArg.second->AComp = m_AnimationComponent;
	}
	else if (key == SDLK_f)
	{
		m_FpPairEventArg.second->PComp = std::reference_wrapper<PositionComponent>(m_MoveComponent->m_PositionComponent);
		if (m_Owner.IsAnimated) m_FpPairEventArg.second->AComp = m_AnimationComponent;
	}

	m_FpPairEventArg.first = std::function<void(EventArgs*)>(m_EventFactory->ReturnEventLamdaKeyDown(key));
	NotifyStateEvent();
}

void dae::EventGenComponent::GenerateKeyUpEvent(SDL_Keycode type)
{
	m_FpPairEventArg.second->MComp = std::reference_wrapper<MoveComponent>(*m_MoveComponent);
	m_FpPairEventArg.first = std::function<void(EventArgs*)>(m_EventFactory->ReturnEventLamdaUp(type));
	if (m_Owner.IsAnimated) m_FpPairEventArg.second->AComp = m_AnimationComponent;
	NotifyStateEvent();
}

void dae::EventGenComponent::NotifyStateEvent()
{
	m_StateComponent->NotifyonEvent(m_FpPairEventArg); 
}

void dae::EventGenComponent::Update(float )
{
}
