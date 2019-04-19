#pragma once
#include "ComponentsH.h"

namespace dae {
	struct AnimationFrame
	{
		AnimationFrame() = delete; 
		AnimationFrame(Vec2 Uv) : uv(Uv) {}; 
		Vec2 uv;
		
	};
	struct AnimationClip
	{
	public:
		AnimationClip() = delete; 
		AnimationClip(unsigned int framecount) : m_AmountOfFrames(framecount) { };
		std::vector<AnimationFrame>  m_Frames;
		unsigned int m_TickDuration = 30, m_AmountOfFrames;
		void AddFrame(Vec2 uv) { m_Frames.push_back(AnimationFrame(uv)); }
	};
	class AnimationComponent : public BaseComponent {
	public: 
		AnimationComponent() = delete;
		AnimationComponent(unsigned char activeAnim) : m_ActiveAnimationId(activeAnim) { m_CurrentFrame = 0; };
		~AnimationComponent() {};
		unsigned int m_CurrentTickCounter = 0, m_TextureId, m_ActiveAnimationId = 0, m_CurrentFrame =0;
		virtual void Update(float dt) override; 
		void CreateAnimation(Vec2 startuv, unsigned int AmountOfFrames, int texsize =32 ) 
		{
			AnimationClip ac(AmountOfFrames); 	
			for (unsigned int i = 0; i < AmountOfFrames; i++)
				ac.AddFrame(Vec2(startuv.x + i * texsize, startuv.y));
			m_Animations.push_back(ac);
		}
		Vec2 GetCurrentUv() { auto clip = m_Animations[m_ActiveAnimationId];  return clip.m_Frames[m_CurrentFrame].uv; }

		std::vector<AnimationClip> m_Animations; 
	};
}