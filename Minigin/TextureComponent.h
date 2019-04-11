#pragma once
#include "ComponentsH.h"
#include "Texture2D.h"
namespace dae
{
	class TextureComponent :public BaseComponent
	{
	public:
		TextureComponent(std::shared_ptr <GameObject> owner, std::shared_ptr<Texture2D> tex) : BaseComponent(owner),  mTexture(tex) {}
		~TextureComponent();
		void Update(float deltaTime) override;
		//void Receive(int msg, dae::CmpType Destination) override;
		//dae::CmpType GetType() { return dae::CmpType::textureComp; }
		std::shared_ptr<Texture2D> GetTexture() { return mTexture;  }
		void SetTexture(std::shared_ptr<Texture2D> tex) { mTexture = tex; }
	private : 

		std::shared_ptr<Texture2D> mTexture;
	};
}


