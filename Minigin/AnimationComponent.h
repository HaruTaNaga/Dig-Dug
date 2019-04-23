#pragma once
#include "ComponentsH.h"

namespace dae {
	struct AnimationFrame
	{
		AnimationFrame() = delete; 
		AnimationFrame(Vec2 u, Vec2 c = Vec2(32,32)) : uv(u), size(c) {}; 
		Vec2 uv;
		Vec2 size; 
	};
	struct AnimationClip
	{
	public:
		AnimationClip() = delete; 
		AnimationClip(unsigned int framecount, unsigned int duration = 30) : m_AmountOfFrames(framecount) , m_TickDuration(duration) { };
		std::vector<AnimationFrame>  m_Frames;
		unsigned int m_TickDuration, m_AmountOfFrames;
		void AddFrame(Vec2 uv)  {  m_Frames.push_back(AnimationFrame(uv)); }
		void AddClippedFrame(Vec2 uv, Vec2 size) { m_Frames.push_back(AnimationFrame(uv, size)); }
	};


	class AnimationComponent : public BaseComponent {
	public: 
		AnimationComponent() = delete;
		AnimationComponent(unsigned char activeAnim) : m_ActiveAnimationId(activeAnim) { m_CurrentFrame = 0; };
		~AnimationComponent() {};
		unsigned int m_CurrentTickCounter = 0, m_TextureId, m_ActiveAnimationId = 0, m_CurrentFrame =0;
		virtual void Update(float dt) override; 
		void GoToNextFrame();
		void CreateAnimation(Vec2 startuv, unsigned int AmountOfFrames, int texsize =32 ) 
		{
			AnimationClip ac(AmountOfFrames); 	
			for (unsigned int i = 0; i < AmountOfFrames; i++)
				ac.AddFrame(Vec2(startuv.x + i * texsize, startuv.y));
			m_Animations.push_back(ac);
		}
		void CreateHoseAnimation(Vec2 uvR, Vec2 uvL, Vec2 uvB, Vec2 uvT);

		Vec2 GetCurrentClip() { auto clip = m_Animations[m_ActiveAnimationId];  return clip.m_Frames[m_CurrentFrame].uv; }
		bool isFlipped;
		bool FreezeAnimation = false; 
		std::vector<AnimationClip> m_Animations; 
		std::pair<Vec2, Vec2> GetCurrentUv() {
			auto clip = m_Animations[m_ActiveAnimationId];  return { clip.m_Frames[m_CurrentFrame % clip.m_AmountOfFrames].uv, clip.m_Frames[m_CurrentFrame% clip.m_AmountOfFrames].size};
		}
	};
}