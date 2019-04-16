#pragma once
#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MiniginPCH.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "FPSComponent.h"
#include "MapManager.h"
#include "ServiceLocator.h"
#include "PhysicsManager.h"
void dae::SceneLoader::InitialiseNewScene(dae::Levels l)
{
	switch (l)
	{
	case Level1:
		break; 
	case Level2: 
		break;
	case DEMO:
		//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Demo");
		//AddGameObject("background.jpg", Vec2(1, 1));
		//AddGameObject("Logo.png", Vec2(216, 180));
		//AddTextGameObject("DigDug", "Lingua.otf", 2, Vec2(8, 2));
		//AddGameObject("TileTestSprite.png", Vec2(0, 0));
		AddControllableGameObject("DigDugTestSpriteright.png", Vec2(0, 64 + 32), true);
	

		//Add fps loader 
		AddFPSObject(Vec2(5, 5), "Lingua.otf");

	}
}



void dae::SceneLoader::AddGameObject(const std::string & tex, const Vec2 pos)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent();
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add((BaseComponent *)poscmp, go.get());
	go->mPositionCompPtr = poscmp;

	auto texcmpraw = new TextureComponent(ResourceManager::GetInstance().LoadTexture(tex)); 
	Add((BaseComponent *)texcmpraw, go.get());
	go->mTextureCompPtr = texcmpraw;
//	go->SetTexture(tex);
//	go->SetPosition(pos.x, pos.y);
	m_Scene->Add(go);
}
void dae::SceneLoader::AddFPSObject(const Vec2 pos, const std::string & fontname)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent();
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add((BaseComponent *)poscmp, go.get());

	go->mPositionCompPtr = poscmp;
	auto texcmpraw = new TextureComponent( ResourceManager::GetInstance().LoadTexture("Logo.png"));
	Add((BaseComponent *)texcmpraw, go.get());
	go->mTextureCompPtr = texcmpraw;
	auto textcmpraw = new TextComponent(*texcmpraw, "1", ResourceManager::GetInstance().LoadFont(fontname, 13), true);
	Add((BaseComponent *)textcmpraw, go.get());

	auto fpscmpraw = new FPSComponent(*textcmpraw);
	Add((BaseComponent *)fpscmpraw, go.get());

	//	go->SetTexture(tex);
	//	go->SetPosition(pos.x, pos.y);
	m_Scene->Add(go);
}
void dae::SceneLoader::AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize,  const Vec2 pos)
{

	auto font = ResourceManager::GetInstance().LoadFont(fontname, fontsize);
	auto to = std::make_shared<TextObject>(text, font);
	to->SetPosition(pos.x, pos.y);
	//m_Scene->Add(to);

	


}

void dae::SceneLoader::AddControllableGameObject(const std::string & tex, const Vec2 pos, bool IsPlayerOrEnemy  )
{
	UNREFERENCED_PARAMETER(IsPlayerOrEnemy);

	

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();
	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add((BaseComponent *)poscmpraw, goraw);
	go->mPositionCompPtr = poscmpraw;
	TextureComponent * texcmpraw = nullptr;
	if (IsPlayerOrEnemy)
	{
		texcmpraw = new TextureComponent( ResourceManager::GetInstance().LoadTexture(tex));
		Add((BaseComponent *)texcmpraw, goraw);
		go->mTextureCompPtr = texcmpraw;
	}
	else
	{
		//Todo
		//Load Enemy Tex
	}
	auto physicscmpraw = new  PhysicsComponent(go); 
	Add((BaseComponent *)physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent( *poscmpraw, *physicscmpraw);
	Add((BaseComponent *)movecmpraw, goraw);
	auto statecmpraw = new StateComponent();
	Add((BaseComponent*)statecmpraw, goraw);
	auto inputcmpraw = new InputComponent(*movecmpraw,*statecmpraw, go);
	Add((BaseComponent *)inputcmpraw, goraw);
	auto orientationcmpraw = new OrientationComponent( *movecmpraw, *texcmpraw);
	Add((BaseComponent *)orientationcmpraw, goraw);
	if (IsPlayerOrEnemy)
	{
		auto digcmpraw = new  DigComponent( *orientationcmpraw, *poscmpraw, *movecmpraw);
		Add((BaseComponent *)digcmpraw, goraw);
		auto collisioncmpraw = new CollisionComponent( *poscmpraw, *orientationcmpraw, true, false, false);
		Add((BaseComponent*)collisioncmpraw, goraw); 
		
	}
	else
	{
		
	}
	m_Scene->Add(go);

}

void dae::SceneLoader::Add(BaseComponent * comp, GameObject * go)
{
	std::shared_ptr<BaseComponent> physicsCmp;
	physicsCmp.reset(comp);
	go->mComponentvec.push_back(physicsCmp);
}
