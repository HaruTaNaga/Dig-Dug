#pragma once


namespace dae
{
	class Scene;
	class SceneManager final
	{
	public:
		std::shared_ptr<dae::Scene>  CreateScene(const std::string& name);
		~SceneManager(); 
		void Update(const float deltaTime);
		void Render() const;
		Scene * GetActiveScene() { return m_Scenes[m_ActiveSceneIndex].get(); }
		void SetActiveScene(int id);
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIndex = 0; 
	};

}
