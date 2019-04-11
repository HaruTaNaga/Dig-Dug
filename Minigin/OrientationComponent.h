#pragma once
#include "ComponentsH.h"
#include "ResourceManager.h"

namespace dae {

	class OrientationComponent :public BaseComponent
	{
	public:
		OrientationComponent(std::shared_ptr <GameObject>  owner, MoveComponent & movcomp, TextureComponent & texcomp) : BaseComponent(owner), m_MoveComponent(movcomp) , m_TextureComponent(texcomp) {
			m_Textures[0] = ResourceManager::GetInstance().LoadTexture("DigDugTestSpriteright.png");
			m_Textures[1] = ResourceManager::GetInstance().LoadTexture("digdugtestspritedown.png");
			m_Textures[2] = ResourceManager::GetInstance().LoadTexture("digdugtestspriteleft.png");
			m_Textures[3] = ResourceManager::GetInstance().LoadTexture("digdugtestspriteup.png");

		};
		~OrientationComponent();
		void Update(float deltaTime) override;
		//dae::CmpType GetType()  { return dae::CmpType::inputComp; }
		Orientation m_Orientation = dae::Right;
		MoveComponent & m_MoveComponent; 
		TextureComponent & m_TextureComponent;
		std::shared_ptr<Texture2D> m_Textures[4];
	};
}


