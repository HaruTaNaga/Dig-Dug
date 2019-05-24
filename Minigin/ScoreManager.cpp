#include "MiniginPCH.h"
#include "ScoreManager.h"
#include "ScoreUiComponent.h"
void dae::ScoreManager::AddScore(int score )
{
	m_Score += score;  
	m_ScoreUiComponent->Score(m_Score);
}
