#pragma once
namespace dae {

	class SceneObject;
	class EnemyManager {
	public: 
		EnemyManager() {};
		~EnemyManager() {};
		int GetAmountOfEnemies() { return m_AmountOfEnemies;  }
		void SetAmountOfEnemies(int enemies) { m_AmountOfEnemies = enemies; }
		void EnemyKilled() { m_AmountOfEnemies--;}
		void CountEnemiesInActiveScene(std::vector<std::shared_ptr<dae::SceneObject>> so);

	private:

		int  m_AmountOfEnemies = 0; 
		bool m_SceneHasEnemy = false; 

	};

	

	
}