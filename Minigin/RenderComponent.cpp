#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
dae::RenderComponent::RenderComponent(TextureComponent & texcmp, PositionComponent & poscmp) :
	m_PositionComponent(poscmp), 
	m_TextureComponent(texcmp)
{
	m_Renderer = ServiceLocator::GetRenderer(); 

}
dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Update(float )
{
	auto pos = m_PositionComponent.GetPosition();

	m_Renderer->RenderTexture(*m_TextureComponent.GetTexture(), pos.x, pos.y);
}

void dae::RenderComponent::Render()
{
	auto pos = m_PositionComponent.GetPosition();

	m_Renderer->RenderTexture(*m_TextureComponent.GetTexture(), pos.x, pos.y);
}

