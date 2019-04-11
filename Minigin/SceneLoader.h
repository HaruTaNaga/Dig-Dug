#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneLoader : public Singleton<SceneLoader>
	{
	public:
		void InitialiseNewScene(dae::Levels Level);
		void AddGameObject(const std::string & tex, const Vec2 pos);
		void AddFPSObject(const Vec2 pos, const std::string & fontname);
		void AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize, const Vec2 pos); 
		void AddControllableGameObject(const std::string & tex, const Vec2 pos); 

		std::shared_ptr<Scene> m_Scene; 
	};
}


