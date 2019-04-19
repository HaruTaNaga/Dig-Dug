#pragma once

#include <functional>
#include <string>
#include "DataStructs.h"
#include "ComponentsH.h"
namespace dae {
	enum SupportedAnimationLoadingTypes{
		PlayerAnim, 
		EnemyAnim, 
		PookaAnim, 
		FygarAnim
	};
	struct PlayerAnimationData{
		//Name, ClipId, Initial UvOffset, AmountOfFrames
		static const unsigned char AnimationClipCount = 10;
		std::tuple< dae::Vec2, unsigned int,std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(0,0), 1,"Idle" },						//0
			{Vec2(0,0), 2, "WalkingRight"},				//1
			{Vec2(384,0), 2, "WalkingLeft"},			//2
			{Vec2(0,32), 2, "WalkingDown"},				//3
			{Vec2(0,64), 2, "WalkingUp"},				//4
			{Vec2(384,32), 2, "WalkingDownFlipped"},	//5
			{Vec2(384,64), 2, "WalkingUpFlipped"},		//6
			{Vec2(128,0), 2, "Pumping"},				//7
			{Vec2(0,96), 5, "Dying"},					//8
			{Vec2(192, 0), 1, "Winning" }				//9
		};

	};
	class AnimationLoader
	{
	public: 
		void LoadAnimation(AnimationComponent * animComp, SupportedAnimationLoadingTypes t)
		{
			switch (t)
			{
			case PlayerAnim: 
				PlayerAnimationData p; 
				for (int i = 0; i < p.AnimationClipCount; i++)
				{
					animComp->CreateAnimation(std::get<0>(p.AnimationClipData[i]), std::get<1>(p.AnimationClipData[i]));
				}
					


			}
		}
	};
}