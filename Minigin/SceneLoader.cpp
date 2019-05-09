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
		ServiceLocator::GetMapManager()->LoadMap(Levels::Level1);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level1");
		break; 
	case Level2: 
		ServiceLocator::GetMapManager()->LoadMap(Levels::Level2);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level2");
		break;
	case DEMO:
		ServiceLocator::GetMapManager()->LoadMap(Levels::DEMO);
		auto & texName = "SpriteSheet.png";
		auto texture = ServiceLocator::GetResourceManager()->LoadTexturePtr(texName);
		ServiceLocator::GetTextureManager()->AddTexture(texture);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Demo");
		AddPlayer("DigDugTestSpriteright.png", Vec2(0, 64 + 32));
		
		AddEnemy("DigDugTestSpriteright.png", Vec2(32 * 8, 32 * 7));
	
		AddFPSObject(Vec2(96, 32), "Lingua.otf");
		
		AddStaticObject("Rock.Png", Vec2(32 * 8, 32  * 5));

	}
	ServiceLocator::GetPhysicsManager()->InitActiveComponents(); 
	ServiceLocator::GetRenderer()->Setup(); 
}


void dae::SceneLoader::AddFPSObject(const Vec2 pos, const std::string & fontname) 
{
	const auto go = std::make_shared<GameObject>();
	const auto poscmp = new PositionComponent();

	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());

	const auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());

	const auto textcmpraw = new TextComponent(*texcmpraw, "1", ServiceLocator::GetResourceManager()->LoadFont(fontname, 13), true);
	Add(textcmpraw, go.get());

	const auto fpscmpraw = new FPSComponent(*textcmpraw);
	Add(fpscmpraw, go.get());

	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
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

	const auto eventcmpraw = new CommandComponent(*goraw);
	Add(eventcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Hose, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	const auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	const auto hosecmpraw = new HoseComponent(*eventcmpraw, *poscmpraw, *orientationcmpraw, *movecmpraw);
	Add(hosecmpraw, goraw);
	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::HoseAnim);
	Add(animationcmpraw, goraw);


	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw); 

	eventcmpraw->InitComponents();
	m_Scene->Add(go);
	return hosecmpraw; 

}

dae::HpUiComponent * dae::SceneLoader::AddHpUiObject(const Vec2 pos, const std::string & fontname)
{
	const auto go = std::make_shared<GameObject>();
	const auto poscmp = new PositionComponent();

	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());

	const auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());

	const auto textcmpraw = new TextComponent(*texcmpraw, "1", ServiceLocator::GetResourceManager()->LoadFont(fontname, 13), true);
	Add(textcmpraw, go.get());

	const auto hpuicmp = new HpUiComponent(*textcmpraw);
	Add(hpuicmp, go.get());

//	go->mPositionCompPtr = poscmp;
//	go->mTextureCompPtr = texcmpraw;
	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
	Add(rendercmpraw, go.get());
	m_Scene->Add(go);
	return hpuicmp;
}


void dae::SceneLoader::AddEnemy(const std::string & , const Vec2 pos)
{
	

	const auto go = std::make_shared<GameObject>();
	const auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	const auto eventcmpraw = new CommandComponent(*goraw);
	Add(eventcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);
	statecmpraw->NotifyonStateChange(new EnemyState(*statecmpraw));
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Enemy, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::EnemyAnim);
	Add(animationcmpraw, goraw);

//	goraw->m_AnimationCompPtr = animationcmpraw;
	//go->mTextureCompPtr = texcmpraw;
//	go->mPositionCompPtr = poscmpraw;
	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	eventcmpraw->InitComponents();

	m_Scene->Add(go);

}

void dae::SceneLoader::AddPlayer(const std::string & tex, const Vec2 pos)
{

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	TextureComponent * texcmpraw = nullptr;
	texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture(tex));
	Add(texcmpraw, goraw);


	const auto eventcmpraw = new CommandComponent(*goraw);
	Add(eventcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*eventcmpraw);
	Add(statecmpraw, goraw);


	const auto inputcmpraw = new InputComponent(*statecmpraw, *eventcmpraw);
	Add(inputcmpraw, goraw);

	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Player, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	const auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	const auto digcmpraw = new  DigComponent(*orientationcmpraw, *poscmpraw, *movecmpraw);
	Add(digcmpraw, goraw);

	const auto pumpcmpraw = new  PumpComponent(*AddHoseObject(), *orientationcmpraw, *poscmpraw, *eventcmpraw);
	Add(pumpcmpraw, goraw);
	const auto hpcmpraw = new HpComponent(*AddHpUiObject(Vec2(96, 64), "Lingua.otf"));
	Add(hpcmpraw, goraw);
	const auto deathcmpraw = new DeathComponent(*hpcmpraw, *eventcmpraw );
	Add(deathcmpraw, goraw);

	
	

	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::PlayerAnim);
	Add(animationcmpraw, goraw);



	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	eventcmpraw->InitComponents(); 

	m_Scene->Add(go);

}

void dae::SceneLoader::AddStaticObject(const std::string & tex, const Vec2 pos)
{

	const auto go = std::make_shared<GameObject>();
	const auto goraw = go.get();
	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);
	TextureComponent * texcmpraw = nullptr;

	texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture(tex));
	Add(texcmpraw, goraw);
	const auto eventcmpraw = new CommandComponent(*goraw);
	Add(eventcmpraw, goraw);
	const auto collisioncmpraw = new CollisionComponent( CollisionFlags::Static, *eventcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	const auto fallcmpraw = new FallComponent(*poscmpraw, *movecmpraw, *collisioncmpraw);
	Add(fallcmpraw, goraw);
	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmpraw);
	Add(rendercmpraw, goraw);
		m_Scene->Add(go);
}

void dae::SceneLoader::Add(BaseComponent * comp, GameObject * go)
{
	const auto cmp = std::shared_ptr<BaseComponent>(comp);
	go->mComponentvec.push_back(cmp);
}
