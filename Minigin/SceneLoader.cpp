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
		ServiceLocator * sloc = new ServiceLocator; 
		m_Scene = sloc->GetSceneManager()->CreateScene("Demo");
		delete sloc; 
		//AddGameObject("background.jpg", Vec2(1, 1));
		//AddGameObject("Logo.png", Vec2(216, 180));
		//AddTextGameObject("DigDug", "Lingua.otf", 2, Vec2(8, 2));
		//AddGameObject("TileTestSprite.png", Vec2(0, 0));
		AddControllableGameObject("DigDugTestSpriteright.png", Vec2(0, 64 + 32), true);
		for (int y = 0; y < 14; y++)
		{
			for (int x = 0; x < 14; x++)
			{
				//AddGameObject("TileTestSprite2.png", Vec2(x * 32, 96+ (y * 32)));
			}
		}
		//AddGameObject("DigDugTestSprite.png", Vec2(0, 64 ));
		//Add fps loader 
		AddFPSObject(Vec2(5, 5), "Lingua.otf");

	

		//Map
		//auto map = &MapManager::GetInstance(); 
		//map->LoadMap(Levels::DEMO); 
		//auto go = std::shared_ptr<SceneObject>(); 
		//go.reset(map);
		//m_Scene->Add(go);

	}
}



void dae::SceneLoader::AddGameObject(const std::string & tex, const Vec2 pos)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent(go);
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	auto basecmp = (BaseComponent *)poscmp;
	std::shared_ptr<BaseComponent> posCmp;
	posCmp.reset(basecmp);
	go->mPositionCompPtr = poscmp;
	go->mComponentvec.push_back(posCmp);
	auto texcmpraw = new TextureComponent(go, ResourceManager::GetInstance().LoadTexture(tex)); 
	std::shared_ptr<BaseComponent> texCmp; 
	texCmp.reset(texcmpraw); 
	go->mComponentvec.push_back(texCmp);
	go->mTextureCompPtr = texcmpraw;
//	go->SetTexture(tex);
//	go->SetPosition(pos.x, pos.y);
	m_Scene->Add(go);
}
void dae::SceneLoader::AddFPSObject(const Vec2 pos, const std::string & fontname)
{
	auto go = std::make_shared<GameObject>();
	auto poscmp = new PositionComponent(go);
	poscmp->SetPosition(glm::vec3(pos.x, pos.y, 0));
	auto basecomp = (BaseComponent*)poscmp;
	std::shared_ptr<BaseComponent> posCmp;
	posCmp.reset(basecomp);
	go->mComponentvec.push_back(posCmp);
	go->mPositionCompPtr = poscmp;
	auto texcmpraw = new TextureComponent(go, ResourceManager::GetInstance().LoadTexture("Logo.png"));
	std::shared_ptr<BaseComponent> texCmp;
	texCmp.reset(texcmpraw);
	go->mComponentvec.push_back(texCmp);
	go->mTextureCompPtr = texcmpraw;
	auto textcmpraw = new TextComponent(go, *texcmpraw, "1", ResourceManager::GetInstance().LoadFont(fontname, 13), true);
	std::shared_ptr<BaseComponent> textCmp;
	textCmp.reset(textcmpraw);
	go->mComponentvec.push_back(textCmp);

	auto fpscmpraw = new FPSComponent(go, *textcmpraw);
	std::shared_ptr<FPSComponent> fpsComp;
	fpsComp.reset(fpscmpraw);
	go->mComponentvec.push_back(fpsComp);
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

	auto poscmpraw = new PositionComponent(go);
	poscmpraw->SetPosition(glm::vec3(pos.x, pos.y, 0));
	std::shared_ptr<BaseComponent> posCmp;
	posCmp.reset((BaseComponent *)poscmpraw);
	go->mComponentvec.push_back(posCmp);
	go->mPositionCompPtr = poscmpraw;
	TextureComponent * texcmpraw = nullptr;
	if (IsPlayerOrEnemy)
	{
		texcmpraw = new TextureComponent(go, ResourceManager::GetInstance().LoadTexture(tex));
		std::shared_ptr<BaseComponent> texCmp;
		texCmp.reset(texcmpraw);
		go->mComponentvec.push_back(texCmp);
		go->mTextureCompPtr = texcmpraw;

	}
	else
	{
		//Todo
		//Load Enemy Tex
		texcmpraw = new TextureComponent(go, ResourceManager::GetInstance().LoadTexture(tex));
		std::shared_ptr<BaseComponent> texCmp;
		texCmp.reset(texcmpraw);
		go->mComponentvec.push_back(texCmp);
		go->mTextureCompPtr = texcmpraw;
	}
	
	
	auto physicscmpraw = new  PhysicsComponent(go); 
	std::shared_ptr<BaseComponent> physicsCmp;
	physicsCmp.reset((BaseComponent *)physicscmpraw);
	go->mComponentvec.push_back(physicsCmp);

	auto movecmpraw = new MoveComponent(go, *poscmpraw, *physicscmpraw);
	std::shared_ptr<BaseComponent> moveCmp;
	moveCmp.reset((BaseComponent *)movecmpraw);
	go->mComponentvec.push_back(moveCmp);

	auto inputcmpraw = new InputComponent(*movecmpraw, go);
	std::shared_ptr<BaseComponent> inputCmp;
	inputCmp.reset(inputcmpraw);
	go->mComponentvec.push_back(inputCmp);

	auto orientationcmpraw = new OrientationComponent(go, *movecmpraw, *texcmpraw);
	std::shared_ptr<BaseComponent> orientCmp; 
	orientCmp.reset(orientationcmpraw);
	go->mComponentvec.push_back(orientCmp);
	
	if (IsPlayerOrEnemy)
	{
		auto digcmpraw = new  DigComponent(go, *orientationcmpraw, *poscmpraw, *movecmpraw);
		std::shared_ptr<BaseComponent> digCmp;
		digCmp.reset(digcmpraw);
		go->mComponentvec.push_back(digCmp);

	}
	else
	{
		
	}
	m_Scene->Add(go);

	PositionComponent * posc = (PositionComponent*)go->GetComponent<PositionComponent>(); 
	 
	posc->Update(1.0f); 
}