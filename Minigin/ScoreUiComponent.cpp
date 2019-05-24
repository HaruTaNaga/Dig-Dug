#include "MiniginPCH.h"
#include "ScoreUiComponent.h"
#include "TextComponent.h"
dae::ScoreUiComponent::ScoreUiComponent(TextComponent & texc)
	: m_TextComponent(texc)
{
	m_Score = 0; 
	m_TextComponent.SetText("Score : " + std::to_string(m_Score));
}
void dae::ScoreUiComponent::Score(int amount)
{
	
	m_Score += amount;
	m_TextComponent.SetText("Score : " + std::to_string(m_Score));

}
