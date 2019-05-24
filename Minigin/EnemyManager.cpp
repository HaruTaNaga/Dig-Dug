#include "MiniginPCH.h"
#include "EnemyManager.h"

#include "Scene.h"
#include "SceneObject.h"
#include "GameObject.h"
void dae::EnemyManager::CountEnemiesInActiveScene(std::vector<std::shared_ptr<dae::SceneObject>> so)
{
	//auto so = ServiceLocator::GetSceneManager()->GetActiveScene()->GetSceneObjects(); 
	m_AmountOfEnemies = 0; 
	for (auto Obj : so)
	{
		for (auto cmp : dynamic_cast<GameObject*>(Obj.get())->mComponentvec)
		{
			if (dynamic_cast<AiComponent *>(cmp.get()) )
				m_AmountOfEnemies++;
		}

	}
}
