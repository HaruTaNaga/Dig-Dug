#pragma once


namespace dae
{
	class SceneLoader; 
	class Scene;
	class SceneManager final
	{
	public:
		SceneManager(); 
		Scene * CreateScene(const std::string& name);
		//std::shared_ptr<dae::Scene>  CreateScene(const std::string& name);
		~SceneManager(); 
		void Update(const float deltaTime);
		void Render() const;
		void ResetActiveScene();
		Scene * GetActiveScene();

		void SetActiveScene(int id);
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIndex = 0; 
		std::unique_ptr<SceneLoader> m_SceneLoader; 
	};

}
