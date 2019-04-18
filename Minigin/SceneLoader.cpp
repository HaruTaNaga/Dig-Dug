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
		AddPlayer("DigDugTestSpriteright.png", Vec2(0, 64 + 32));
		//AddControllableGameObject("DigDugTestSpriteleft.png", Vec2(0, 128 + 32), true);

		//Add fps loader 
		//AddFPSObject(Vec2(5, 5), "Lingua.otf");
		AddStaticObject("Rock.Png", Vec2(128, 128));

	}
	ServiceLocator::GetPhysicsManager()->InitActiveComponents(); 
}



void dae::SceneLoader::AddGameObject(const std::string & tex, const Vec2 pos)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent();
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());
	go->mPositionCompPtr = poscmp;

	auto texcmpraw = new TextureComponent(ResourceManager::GetInstance().LoadTexture(tex)); 
	Add(texcmpraw, go.get());
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
	Add(poscmp, go.get());

	go->mPositionCompPtr = poscmp;
	auto texcmpraw = new TextureComponent( ResourceManager::GetInstance().LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());
	go->mTextureCompPtr = texcmpraw;
	auto textcmpraw = new TextComponent(*texcmpraw, "1", ResourceManager::GetInstance().LoadFont(fontname, 13), true);
	Add(textcmpraw, go.get());

	auto fpscmpraw = new FPSComponent(*textcmpraw);
	Add(fpscmpraw, go.get());

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

void dae::SceneLoader::AddPlayer(const std::string & tex, const Vec2 pos)
{
	
	

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();
	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);
	go->mPositionCompPtr = poscmpraw;

	TextureComponent * texcmpraw = nullptr;
	texcmpraw = new TextureComponent( ResourceManager::GetInstance().LoadTexture(tex));
	Add(texcmpraw, goraw);
	go->mTextureCompPtr = texcmpraw;

	auto collisioncmpraw = new CollisionComponent(CollisionFlags::Player);
	Add(collisioncmpraw, goraw);
	auto physicscmpraw = new  PhysicsComponent(go, *collisioncmpraw);
	Add(physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent( *poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	auto statecmpraw = new StateComponent();
	Add(statecmpraw, goraw);
	auto eventcmpraw = new EventGenComponent(*goraw);
	Add(eventcmpraw, goraw);
	auto inputcmpraw = new InputComponent(*statecmpraw, *eventcmpraw);
	Add(inputcmpraw, goraw);
	auto orientationcmpraw = new OrientationComponent( *movecmpraw, *texcmpraw);
	Add(orientationcmpraw, goraw);
	auto digcmpraw = new  DigComponent( *orientationcmpraw, *poscmpraw, *movecmpraw);
	Add(digcmpraw, goraw);

		

	
	m_Scene->Add(go);

}

void dae::SceneLoader::AddStaticObject(const std::string & tex, const Vec2 pos)
{

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();
	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);
	go->mPositionCompPtr = poscmpraw;
	TextureComponent * texcmpraw = nullptr;

	texcmpraw = new TextureComponent(ResourceManager::GetInstance().LoadTexture(tex));
	Add(texcmpraw, goraw);
	go->mTextureCompPtr = texcmpraw;
	auto collisioncmpraw = new CollisionComponent( CollisionFlags::Static);
	Add(collisioncmpraw, goraw);
	m_Scene->Add(go);
}

void dae::SceneLoader::Add(BaseComponent * comp, GameObject * go)
{
	std::shared_ptr<BaseComponent> physicsCmp;
	physicsCmp.reset(comp);
	go->mComponentvec.push_back(physicsCmp);
}
