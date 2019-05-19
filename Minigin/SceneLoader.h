#pragma once

#include "BaseComponent.h"
#include  "GameObject.h"
#include "AnimationData.h"
namespace dae
{
	class AnimationLoader; 
	class Scene;
	//class AiComponent;
	class SceneLoader
	{
	public:
		void ResetActiveScene(dae::Levels l);
		void InitialiseNewScene(dae::Levels Level);
		//void AddGameObject(const std::string & tex, const Vec2 pos);
		void AddFPSObject(const Vec2 pos, const std::string & fontname);
		dae::FireComponent * AddFireObject();
		HoseComponent * AddHoseObject();
		HpUiComponent * AddHpUiObject(const Vec2 pos, const std::string & fontname);
		//void AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize, const Vec2 pos); 
		void AddPlayer(const Vec2 pos, PlayerTypes id, const Vec2 UIpos);
		void AddPooka( const Vec2 pos);
		void AddFygar(const Vec2 pos);
		void AddStaticObject(const std::string & tex,const Vec2 pos );

		void AddTextObject(const Vec2 pos, const std::string & text, int size);
		void AddMainMenu();

		void ResetScene(dae::Levels newLevelType); 

		void Add(BaseComponent * comp, GameObject * go);
		AnimationLoader animLoader;
		Scene * m_Scene; 
	};
}


