#pragma once
#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"

#include "TextObject.h"
#include "FPSComponent.h"
#include "MapManager.h"
#include "ServiceLocator.h"
#include "PhysicsManager.h"
#include "AnimationData.h"
#include "AiComponent.h"
#include "GameOverObserver.h"
void dae::SceneLoader::ResetActiveScene(dae::Levels l)
{

	m_Scene = ServiceLocator::GetSceneManager()->GetActiveScene();
	m_Scene->ResetScene();

	switch (l)
	{

	case LevelSinglePlayer:
		//ServiceLocator::GetMapManager()->LoadMap(Levels::LevelSinglePlayer);
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 6, 32 * 7)); 
		break;
	case LevelCoop:
		//ServiceLocator::GetMapManager()->LoadMap(Levels::LevelCoop);
		//m_Scene = ServiceLocator::GetSceneManager()->CreateScene("LevelCoop");
		AddPlayer(Vec2(32, 96), PlayerTypes::PlayerOne, Vec2(32, 32));
		AddPlayer(Vec2(12 * 32, 96), PlayerTypes::PlayerTwo, Vec2(320, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 5, 32 * 7));
		break;
	case LevelVersus:
		//ServiceLocator::GetMapManager()->LoadMap(Levels::LevelVersus);
		//m_Scene = ServiceLocator::GetSceneManager()->CreateScene("LevelVersus");
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		//AddPlayer(Vec2(0, 64 + 32), PlayerTypes::Fygar);
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 5, 32 * 7));
		break;

	

	}
	AddFPSObject(Vec2(8, 8), "Lingua.otf");
	ServiceLocator::GetPhysicsManager()->InitActiveComponents();
	ServiceLocator::GetRenderer()->Setup();
}
void dae::SceneLoader::InitialiseNewScene(dae::Levels l)
{
	auto & texName = "SpriteSheet.png";
	auto texture = ServiceLocator::GetResourceManager()->LoadTexturePtr(texName);
	ServiceLocator::GetTextureManager()->AddTexture(texture);
	switch (l)
	{
	case MenuLevel:
		ServiceLocator::GetMapManager()->LoadMap(Levels::MenuLevel);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("MenuLevel");
		AddMainMenu();
		break; 
	case LevelSinglePlayer:
		ServiceLocator::GetMapManager()->LoadMap(Levels::LevelSinglePlayer);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("LevelSinglePlayer");
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 6, 32 * 7));
		break;
	case LevelCoop: 
		ServiceLocator::GetMapManager()->LoadMap(Levels::LevelCoop);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("LevelCoop");
		AddPlayer(Vec2(32, 96), PlayerTypes::PlayerOne, Vec2(32, 32));
		AddPlayer(Vec2(12*32,96  ), PlayerTypes::PlayerTwo, Vec2(320, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 5, 32 * 7));
		break; 
	case LevelVersus: 
		ServiceLocator::GetMapManager()->LoadMap(Levels::LevelVersus);
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("LevelVersus");
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		//AddPlayer(Vec2(0, 64 + 32), PlayerTypes::Fygar);
		AddPooka(Vec2(32 * 8, 32 * 7));

		AddFygar(Vec2(32 * 5, 32 * 7));
		break;

	case DEMO:
		ServiceLocator::GetMapManager()->LoadMap(Levels::DEMO);
		
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Demo");
		AddPlayer( Vec2(0, 64 + 32),PlayerTypes::PlayerOne, Vec2(96,32));

		AddFygar(Vec2(32 * 5, 32 * 7));
		AddPooka(Vec2(32 * 8, 32 * 7));
		AddPooka(Vec2(32 * 4, 32 * 7));
		//AddFPSObject(Vec2(96, 32), "Lingua.otf");
		AddStaticObject("Rock.Png", Vec2(32 * 8, 32  * 5));

	}
	AddFPSObject(Vec2(8, 8), "Lingua.otf");
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

dae::FireComponent * dae::SceneLoader::AddFireObject() 
{
	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(0, 0, 0));
	Add(poscmpraw, goraw);

	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Fire, *commandcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);

	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::FireAnim);
	Add(animationcmpraw, goraw);
	const auto firecmpraw = new FireComponent(*poscmpraw, *animationcmpraw );
	Add(firecmpraw, goraw);

	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	collisioncmpraw->m_FireComponent = firecmpraw;
	collisioncmpraw->m_PositionComponent = poscmpraw;
	commandcmpraw->InitComponents();

	m_Scene->Add(go);
	return firecmpraw;
}

 dae::HoseComponent * dae::SceneLoader::AddHoseObject()
{
	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(999, 999, 0));
	Add(poscmpraw, goraw);

	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Hose, *commandcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	const auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	const auto hosecmpraw = new HoseComponent(*commandcmpraw, *poscmpraw, *orientationcmpraw, *movecmpraw);
	Add(hosecmpraw, goraw);
	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::HoseAnim);
	Add(animationcmpraw, goraw);


	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw); 

	commandcmpraw->InitComponents();
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

	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
	Add(rendercmpraw, go.get());
	m_Scene->Add(go);
	return hpuicmp;
}


void dae::SceneLoader::AddPooka( const Vec2 pos)
{
	

	const auto go = std::make_shared<GameObject>();
	const auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);
	statecmpraw->NotifyonStateChange(new EnemyState(*statecmpraw));
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Enemy, *commandcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::PookaAnim);
	Add(animationcmpraw, goraw);

	

//	goraw->m_AnimationCompPtr = animationcmpraw;
	//go->mTextureCompPtr = texcmpraw;
//	go->mPositionCompPtr = poscmpraw;
	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	commandcmpraw->InitComponents();

	AiComponent * AiComponent = new dae::AiComponent(Pooka, *statecmpraw, *poscmpraw, *movecmpraw, *animationcmpraw, *collisioncmpraw);
	Add(AiComponent, goraw);

	m_Scene->Add(go);

}

void dae::SceneLoader::AddFygar(const Vec2 pos)
{


	const auto go = std::make_shared<GameObject>();
	const auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);
	statecmpraw->NotifyonStateChange(new EnemyState(*statecmpraw));
	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Enemy, *commandcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);
	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::FygarAnim);
	Add(animationcmpraw, goraw);
	const auto fygaroricmpraw = new FygarOrientationComponent(*movecmpraw);
	Add(fygaroricmpraw, goraw);
	const auto firebreathcmpraw = new  FireBreathComponent(*fygaroricmpraw, *AddFireObject(), *poscmpraw);
	Add(firebreathcmpraw, goraw);
	//	goraw->m_AnimationCompPtr = animationcmpraw;
		//go->mTextureCompPtr = texcmpraw;
	//	go->mPositionCompPtr = poscmpraw;
	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	commandcmpraw->InitComponents();

	AiComponent * aicmpraw = new dae::AiComponent(Fygar, *statecmpraw, *poscmpraw, *movecmpraw, *animationcmpraw, *collisioncmpraw);
	Add(aicmpraw, goraw);
	aicmpraw->m_FireBreathComponent = firebreathcmpraw; 
	m_Scene->Add(go);

}

void dae::SceneLoader::AddPlayer(const Vec2 pos, PlayerTypes id, const Vec2 UiPos)
{

	auto go = std::make_shared<GameObject>();
	auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmpraw, goraw);


	//TextureComponent * texcmpraw = nullptr;
	//texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture(tex));
	//Add(texcmpraw, goraw);


	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);


	const auto inputcmpraw = new InputComponent(*statecmpraw, *commandcmpraw,id);
	Add(inputcmpraw, goraw);

	const auto collisioncmpraw = new CollisionComponent(CollisionFlags::Player, *commandcmpraw);
	Add(collisioncmpraw, goraw);
	const auto physicscmpraw = new  PhysicsComponent(*collisioncmpraw);
	Add(physicscmpraw, goraw);
	const auto movecmpraw = new MoveComponent(*poscmpraw, *physicscmpraw);
	Add(movecmpraw, goraw);

	const auto orientationcmpraw = new OrientationComponent(*movecmpraw);
	Add(orientationcmpraw, goraw);
	const auto digcmpraw = new  DigComponent(*orientationcmpraw, *poscmpraw, *movecmpraw);
	Add(digcmpraw, goraw);

	const auto pumpcmpraw = new  PumpComponent(*AddHoseObject(), *orientationcmpraw, *poscmpraw, *commandcmpraw);
	Add(pumpcmpraw, goraw);
	const auto hpcmpraw = new HpComponent(*AddHpUiObject(Vec2(UiPos.x, UiPos.y), "Lingua.otf"));
	Add(hpcmpraw, goraw);
	hpcmpraw->AddObserver(new GameOverObserver());
	const auto deathcmpraw = new DeathComponent(*hpcmpraw );
	Add(deathcmpraw, goraw);

	
	

	const auto animationcmpraw = new AnimationComponent(0);
	animLoader.LoadAnimation(animationcmpraw, SupportedAnimationLoadingTypes::PlayerAnim);
	Add(animationcmpraw, goraw);



	const auto animatedrendercmpraw = new AnimatedRenderComponent(*animationcmpraw, *poscmpraw, 0);
	Add(animatedrendercmpraw, goraw);
	commandcmpraw->InitComponents(); 



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
	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto collisioncmpraw = new CollisionComponent( CollisionFlags::Static, *commandcmpraw);
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
void dae::SceneLoader::AddTextObject(const Vec2 pos, const std::string & text, int size)
{
	auto go = std::make_shared<GameObject>();
	//auto goraw = go.get();
	const auto poscmp = new PositionComponent();
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	Add(poscmp, go.get());

	const auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("Logo.png"));
	Add(texcmpraw, go.get());

	const auto textcmpraw = new TextComponent(*texcmpraw, text, ServiceLocator::GetResourceManager()->LoadFont("Lingua.otf", size), true);
	Add(textcmpraw, go.get());
	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmp);
	Add(rendercmpraw, go.get());
	m_Scene->Add(go);
}
void dae::SceneLoader::AddMainMenu()
{

	auto go = std::make_shared<GameObject>(); //menu
	auto goraw = go.get();

	const auto poscmpraw = new PositionComponent();
	poscmpraw->SetPosition(glm::vec3(96, 64 + 128, 0));
	Add(poscmpraw, goraw);
	const auto commandcmpraw = new CommandComponent(*goraw);
	Add(commandcmpraw, goraw);
	const auto statecmpraw = new StateComponent(*commandcmpraw);
	Add(statecmpraw, goraw);
	auto menucmpraw = new MenuComponent(); 
	menucmpraw->AddMenuOption(Vec2(96,64+128), Levels::LevelSinglePlayer, 2);
	AddTextObject(Vec2(96  + 32, 8+64 + 128), "Single player", 17); 
	menucmpraw->AddMenuOption(Vec2(96, 64+192), Levels::LevelCoop, 3);
	AddTextObject(Vec2(96 + 32, 8+64 + 192), "Co-op Multi player", 17);
	menucmpraw->AddMenuOption(Vec2(96, 64+254), Levels::LevelVersus, 4);
	AddTextObject(Vec2(96 + 32, 8+64 + 254), "Versus Multi player", 17);
	AddTextObject(Vec2(120, 64), "DIG DUG", 40);
	Add(menucmpraw, goraw);
	auto texcmpraw = new TextureComponent(ServiceLocator::GetResourceManager()->LoadTexture("IndicatorSpriteLarge.png"));
	Add(texcmpraw, goraw);
	const auto inputcmpraw = new InputComponent(*statecmpraw, *commandcmpraw, PlayerTypes::Menu);
	Add(inputcmpraw, goraw);
	const auto rendercmpraw = new RenderComponent(*texcmpraw, *poscmpraw);
	Add(rendercmpraw, go.get());

	commandcmpraw->InitComponents();
	m_Scene->Add(go);


}
/*
void dae::SceneLoader::ResetScene(dae::Levels newLevelType)
{
	m_Scene.reset(ServiceLocator::GetSceneManager()->GetActiveScene()); 
	m_Scene->GetSceneObjects().clear(); 

	switch (newLevelType)
	{

	case LevelSinglePlayer:
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));
		AddFygar(Vec2(32 * 5, 32 * 7)); 
		break;
	case LevelCoop:
		AddPlayer(Vec2(32, 96), PlayerTypes::PlayerOne, Vec2(32, 32));
		AddPlayer(Vec2(12 * 32, 96), PlayerTypes::PlayerTwo, Vec2(320, 32));
		break;
	case LevelVersus:
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));

		break;

	case DEMO:
		AddPlayer(Vec2(0, 64 + 32), PlayerTypes::PlayerOne, Vec2(96, 32));
		AddPooka(Vec2(32 * 8, 32 * 7));
		AddPooka(Vec2(32 * 4, 32 * 7));
		AddStaticObject("Rock.Png", Vec2(32 * 8, 32 * 5));
		break;
	default: 
		return;

	}
	AddFPSObject(Vec2(8, 8), "Lingua.otf");
	ServiceLocator::GetPhysicsManager()->InitActiveComponents();
	ServiceLocator::GetRenderer()->Setup();
	ServiceLocator::GetMapManager();
}
*/


void dae::SceneLoader::Add(BaseComponent * comp, GameObject * go)
{
	const auto cmp = std::shared_ptr<BaseComponent>(comp);
	go->mComponentvec.push_back(cmp);
}
