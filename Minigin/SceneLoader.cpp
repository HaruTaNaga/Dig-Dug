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
#include "AnimationData.h"
void dae::SceneLoader::InitialiseNewScene(dae::Levels l)
{
	switch (l)
	{
	case Level1:
		break; 
	case Level2: 
		break;
	case DEMO:
		auto & texName = "SpriteSheet.png";
		auto texture = ServiceLocator::GetResourceManager()->LoadTexturePtr(texName);
		ServiceLocator::GetTextureManager()->AddTexture(texture);
		//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Demo");
		//AddGameObject("background.jpg", Vec2(1, 1));
		//AddGameObject("Logo.png", Vec2(216, 180));
		//AddTextGameObject("DigDug", "Lingua.otf", 2, Vec2(8, 2));
		//AddGameObject("TileTestSprite.png", Vec2(0, 0));
		AddPlayer("DigDugTestSpriteright.png", Vec2(0, 64 + 32));
		//AddControllableGameObject("DigDugTestSpriteleft.png", Vec2(0, 128 + 32), true);
		AddEnemy("DigDugTestSpriteright.png", Vec2(32 * 8, 32 * 7));
		//Add fps loader 
		AddFPSObject(Vec2(96, 32), "Lingua.otf");
		//AddHoseObject(Vec2(10, 20));
		AddStaticObject("Rock.Png", Vec2(32 * 8, 32  * 5));

	}
	ServiceLocator::GetPhysicsManager()->InitActiveComponents(); 
	ServiceLocator::GetRenderer()->Setup(); 
}


/*
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

void dae::SceneLoader::AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize,  const Vec2 pos)
{

	auto font = ResourceManager::GetInstance().LoadFont(fontname, fontsize);
	auto to = std::make_shared<TextObject>(text, font);
	to->SetPosition(pos.x, pos.y);
	//m_Scene->Add(to);

	


}
*/

void dae::SceneLoader::AddFPSObject(const Vec2 pos, const std::string & fontname)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent();

	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());

	auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());

	auto textcmpraw = new TextComponent(*texcmpraw, "1", ServiceLocator::GetResourceManager()->LoadFont(fontname, 13), true);
	Add(textcmpraw, go.get());

	auto fpscmpraw = new FPSComponent(*textcmpraw);
	Add(fpscmpraw, go.get());

	go->mPositionCompPtr = poscmp;
	go->mTextureCompPtr = texcmpraw;
	auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
	Add(rendercmpraw, go.get());
	m_Scene->Add(go);
}


dae::HoseComponent * dae::SceneLoader::AddHoseObject()
{
	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(999, 999, 0));
	Add(poscmpraw, goraw);

	/*
	TextureComponent * texcmpraw = nullptr;
	texcmpraw = new TextureComponent(ResourceManager::GetInstance().LoadTexture(tex));
	Add(texcmpraw, goraw);*/


	auto eventcmpraw = new EventGenComponent(*goraw);
	Add(eventcmpraw, goraw);
	auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);
	auto collisioncmpraw = new CollisionComponent(CollisionFlags::Hose, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	auto hosecmpraw = new HoseComponent(*eventcmpraw, *poscmpraw, *orientationcmpraw, *movecmpraw); 
	Add(hosecmpraw, goraw);
	auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::HoseAnim);
	Add(animationcmpraw, goraw);
	goraw->IsAnimated = true;
	goraw->m_AnimationCompPtr = animationcmpraw;
	//go->mTextureCompPtr = texcmpraw;
	go->mPositionCompPtr = poscmpraw;

	auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw); 

	//eventcmpraw->InitComponents();
	eventcmpraw->InitComponents();
	m_Scene->Add(go);
	return hosecmpraw; 

}

dae::HpUiComponent * dae::SceneLoader::AddHpUiObject(const Vec2 pos, const std::string & fontname)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent();

	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());

	auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());

	auto textcmpraw = new TextComponent(*texcmpraw, "1", ServiceLocator::GetResourceManager()->LoadFont(fontname, 13), true);
	Add(textcmpraw, go.get());

	auto hpuicmp = new HpUiComponent(*textcmpraw);
	Add(hpuicmp, go.get());

	go->mPositionCompPtr = poscmp;
	go->mTextureCompPtr = texcmpraw;
	auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
	Add(rendercmpraw, go.get());
	m_Scene->Add(go);
	return hpuicmp;
}


void dae::SceneLoader::AddEnemy(const std::string & , const Vec2 pos)
{
	

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	auto eventcmpraw = new EventGenComponent(*goraw);
	Add(eventcmpraw, goraw);
	auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);
	statecmpraw->NotifyonStateChange(new EnemyState(*statecmpraw));
	auto collisioncmpraw = new CollisionComponent(CollisionFlags::Enemy, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::EnemyAnim);
	Add(animationcmpraw, goraw);
	goraw->IsAnimated = true;
	goraw->m_AnimationCompPtr = animationcmpraw;
	//go->mTextureCompPtr = texcmpraw;
	go->mPositionCompPtr = poscmpraw;
	auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	eventcmpraw->InitComponents();

	m_Scene->Add(go);

}

void dae::SceneLoader::AddPlayer(const std::string & tex, const Vec2 pos)
{

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	TextureComponent * texcmpraw = nullptr;
	texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture(tex));
	Add(texcmpraw, goraw);


	auto eventcmpraw = new EventGenComponent(*goraw);
	Add(eventcmpraw, goraw);
	auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);


	auto inputcmpraw = new InputComponent(*statecmpraw, *eventcmpraw);
	Add(inputcmpraw, goraw);

	auto collisioncmpraw = new CollisionComponent(CollisionFlags::Player, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	auto digcmpraw = new  DigComponent(*orientationcmpraw, *poscmpraw, *movecmpraw);
	Add(digcmpraw, goraw);

	auto pumpcmpraw = new  PumpComponent(*AddHoseObject(), *orientationcmpraw, *poscmpraw, *eventcmpraw);
	Add(pumpcmpraw, goraw);
	auto hpcmpraw = new HpComponent(*AddHpUiObject(Vec2(96, 64), "Lingua.otf"));
	Add(hpcmpraw, goraw);
	auto deathcmpraw = new DeathComponent(*hpcmpraw, *eventcmpraw );
	Add(deathcmpraw, goraw);

	
	

	auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::PlayerAnim);
	Add(animationcmpraw, goraw);
	goraw->IsAnimated = true;


	go->m_AnimationCompPtr = animationcmpraw;
	//go->mTextureCompPtr = texcmpraw;
	go->mPositionCompPtr = poscmpraw;
	auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	eventcmpraw->InitComponents(); 

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

	texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture(tex));
	Add(texcmpraw, goraw);
	go->mTextureCompPtr = texcmpraw;
	auto eventcmpraw = new EventGenComponent(*goraw);
	Add(eventcmpraw, goraw);
	auto collisioncmpraw = new CollisionComponent( CollisionFlags::Static, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	auto fallcmpraw = new FallComponent(*poscmpraw, *movecmpraw, *collisioncmpraw);
	Add(fallcmpraw, goraw);
	auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmpraw);
	Add(rendercmpraw, goraw);
		m_Scene->Add(go);
}

void dae::SceneLoader::Add(BaseComponent * comp, GameObject * go)
{
	std::shared_ptr<BaseComponent> physicsCmp;
	physicsCmp.reset(comp);
	go->mComponentvec.push_back(physicsCmp);
}
