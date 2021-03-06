#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend dae::Scene *  SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(const float deltaTime);
		void Render() const;
		void ResetScene() { mObjects.clear(); }
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		std::vector<std::shared_ptr<SceneObject>> GetSceneObjects() { return mObjects; }
	private: 
		explicit Scene(const std::string& name);

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
