#pragma once

#include "BaseComponent.h"
#include  "GameObject.h"
#include "AnimationData.h"
namespace dae
{
	class AnimationLoader; 
	class Scene;
	class SceneLoader
	{
	public:
		void InitialiseNewScene(dae::Levels Level);
		//void AddGameObject(const std::string & tex, const Vec2 pos);
		void AddFPSObject(const Vec2 pos, const std::string & fontname);
		HoseComponent * AddHoseObject();
		HpUiComponent * AddHpUiObject(const Vec2 pos, const std::string & fontname);
		//void AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize, const Vec2 pos); 
		void AddPlayer(const std::string & tex, const Vec2 pos);
		void AddEnemy(const std::string & tex, const Vec2 pos);
		void AddStaticObject(const std::string & tex,const Vec2 pos );
		void Add(BaseComponent * comp, GameObject * go);
		AnimationLoader animLoader;
		std::shared_ptr<Scene> m_Scene; 
	};
}


