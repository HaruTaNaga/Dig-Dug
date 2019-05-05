#pragma once
#include "ComponentsH.h"
namespace dae
{
	class AnimatedRenderComponent :public BaseRenderComponent
	{
	public:
		AnimatedRenderComponent(AnimationComponent & anicmp, PositionComponent & poscmp, int TextureId);
		virtual ~AnimatedRenderComponent();
		void Update(float deltaTime) override;
		void Render() override; 

	private:
		Renderer * m_Renderer;
		Texture2D * m_Texture; 
		PositionComponent & m_PositionComponent;
		AnimationComponent & m_AnimationComponent; 


	};
}
