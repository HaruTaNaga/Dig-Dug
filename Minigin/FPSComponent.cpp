#include "MiniginPCH.h"
#include "FPSComponent.h"


dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update(float deltaTime)
{

	auto fps = 1.0f / deltaTime; 
	fps = roundf(fps);

	m_FrameCtr += 1;
	if (m_FrameCtr > m_FramesPerUpdate)
	{
		m_TextComponent.SetText(std::to_string(int(fps))+ " fps      " +std::to_string(deltaTime) + "  ms"  );
		m_FrameCtr = 0; 
	}
	
	
}
