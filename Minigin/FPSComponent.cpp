#include "MiniginPCH.h"
#include "FPSComponent.h"


dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	auto fps = 1.0f / deltaTime; 
	fps = roundf(fps);
	m_TextComponent.SetText(std::to_string(deltaTime) + "ms / fps :" + std::to_string(fps)); 
	
}
