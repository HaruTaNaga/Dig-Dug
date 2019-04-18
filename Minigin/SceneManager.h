#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final //: public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<dae::Scene>  CreateScene(const std::string& name);

		void Update(const float deltaTime);
		void Render();
		Scene * GetActiveScene() { return mScenes[0].get(); }
	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		int ActiveSceneIndex = 0; 
	};

}
