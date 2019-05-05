#pragma once
#include "ComponentsH.h"
namespace dae
{
	class RenderComponent :public BaseRenderComponent
	{
	public:
		RenderComponent(TextureComponent & texcmp, PositionComponent & poscmp);
		virtual ~RenderComponent();
		void Update(float deltaTime) override;
		void Render() override; 

	private:
		Renderer * m_Renderer; 
		TextureComponent & m_TextureComponent; 
		PositionComponent & m_PositionComponent; 

		
	};
}


