#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include  "ComponentsH.h"
#include "ServiceLocator.h"
dae::GameObject::GameObject()
{

	m_Renderer = ServiceLocator::GetRenderer();

}
dae::GameObject::~GameObject() {
	
};

void dae::GameObject::Update(const float deltaTime)
{
	for (auto comp : mComponentvec)
	{
		comp->Update(deltaTime);
	}

}
/*
void dae::GameObject::Render() const
{
	//auto poscomp = (PositionComponent *)mComponentvec[mPositionCompIndex].get();
	//auto posComp = std::reinterpret_pointer_cast<PositionComponent>(mComponentvec[mPositionCompIndex]);
	/*
	auto pos = mPositionCompPtr->GetPosition();


	if (IsAnimated)
	{
		auto texMngr = ServiceLocator::GetTextureManager();
		auto tex = texMngr->m_Textures[0];
		auto uv = m_AnimationCompPtr->GetCurrentUv();

		m_Renderer->RenderAnimation(*tex, pos.x, pos.y, uv.first.x, uv.first.y, uv.second.x,uv.second.y);
		//m_Renderer->RenderTexture(*tex, pos.x, pos.y);
	}
	else
	{
		m_Renderer->RenderTexture(*mTextureCompPtr->GetTexture(), pos.x, pos.y);
	}*/
	

//}
/*
void dae::GameObject::SetTexture(const std::string& filename)
{
	if (mTextureCompPtr != nullptr)
	{
		mTextureCompPtr->SetTexture(ServiceLocator::GetResourceManager()->LoadTexture(filename));
	}
	
}*/
/*
void dae::GameObject::SetPosition(float x, float y)
{
	if (mPositionCompPtr != nullptr)
	{
		mPositionCompPtr->SetPosition(x, y, 0.0f);
	}
	
}

//const std::shared_ptr<dae::BaseComponent> dae::GameObject::GetComponent(dae::CmpType type)
{
	
	auto comp = mComponentvec.begin(); 
	
	while ((**comp).GetType() != type)
	{
		if (++comp == mComponentvec.end())
			std::cout << "Component not found:" << type << std::endl; 
	}

	return *comp; 
	
}*/
/*
//void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> comp)
{
	//TODO: check duplicates

	
	mComponentvec.push_back(comp); 
	switch (comp->GetType())
	{
	case dae::CmpType::posComp:
		mPositionCompPtr = (PositionComponent *)comp.get();
		break;
	case dae::CmpType::textureComp:
		mTextureCompPtr = (TextureComponent*)comp.get();
		break;

	}
	

}
*/