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
		static const unsigned char AnimationClipCount = 15;
		std::tuple< dae::Vec2, unsigned int,std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(0,0), 1,"IdleRight" },				//0
			{Vec2(384+32,0), 1, "IdleLeft"},			//1
			{Vec2(0,32), 1, "IdleDown"},				//2
			{Vec2(0,64), 1, "IdleUp"},				    //3
			{Vec2(0,32), 1, "IdleDownFlipped"},			//4
			{Vec2(0,64), 1, "IdleUpFlipped"},		    //5
			{Vec2(0,0), 2, "WalkingRight"},				//6
			{Vec2(384,0), 2, "WalkingLeft"},			//7
			{Vec2(0,32), 2, "WalkingDown"},				//8
			{Vec2(0,64), 2, "WalkingUp"},				//9
			{Vec2(384,32), 2, "WalkingDownFlipped"},	//10
			{Vec2(384,64), 2, "WalkingUpFlipped"},		//11
			{Vec2(128,0), 2, "Pumping"},				//12
			{Vec2(0,96), 5, "Dying"},					//13
			{Vec2(192, 0), 1, "Winning" }				//14
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