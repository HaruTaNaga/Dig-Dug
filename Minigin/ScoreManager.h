#pragma once
namespace dae {
	class ScoreUiComponent; 

	class ScoreManager {
	public: 
		ScoreManager() {};
		~ScoreManager() {};
		void AddScore(int score); 
		int m_Score = 0; 
		ScoreUiComponent * m_ScoreUiComponent; 

	};
}