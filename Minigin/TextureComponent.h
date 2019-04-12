#pragma once
#include "ComponentsH.h"
#include "Texture2D.h"
namespace dae
{
	class TextureComponent :public BaseComponent
	{
	public:
		TextureComponent(std::shared_ptr <GameObject> owner, std::shared_ptr<Texture2D> tex) : BaseComponent(owner), m_Texture(tex) {}
		~TextureComponent();
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::textureComp; }
		std::shared_ptr<Texture2D> GetTexture() { return m_Texture;  }
		void SetTexture(std::shared_ptr<Texture2D> tex) { m_Texture = tex; }
	private : 

		std::shared_ptr<Texture2D> m_Texture;
	};
}


