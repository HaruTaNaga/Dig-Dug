#include "MiniginPCH.h"
#include "AnimatedRenderComponent.h"

dae::AnimatedRenderComponent::AnimatedRenderComponent(AnimationComponent & anicmp, PositionComponent & poscmp, int TextureId = 0) : 
m_PositionComponent(poscmp),
m_AnimationComponent(anicmp)
{
	m_Renderer = ServiceLocator::GetRenderer();
	auto texMngr = ServiceLocator::GetTextureManager();
	m_Texture = texMngr->m_Textures[TextureId]; 

}

dae::AnimatedRenderComponent::~AnimatedRenderComponent()
{
}

void dae::AnimatedRenderComponent::Update(float )
{

	auto uv = m_AnimationComponent.GetCurrentUv();
	auto pos = m_PositionComponent.GetPosition(); 

	m_Renderer->RenderAnimation(*m_Texture, pos.x, pos.y, uv.first.x, uv.first.y, uv.second.x, uv.second.y);
	//m_Renderer->RenderTexture(*tex, pos.x, pos.y);
}

void dae::AnimatedRenderComponent::Render()
{
	auto uv = m_AnimationComponent.GetCurrentUv();
	auto pos = m_PositionComponent.GetPosition();

	m_Renderer->RenderAnimation(*m_Texture, pos.x, pos.y, uv.first.x, uv.first.y, uv.second.x, uv.second.y);
	//m_Renderer->RenderTexture(*tex, pos.x, pos.y);
}
