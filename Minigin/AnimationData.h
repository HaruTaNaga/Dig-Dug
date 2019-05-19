#pragma once

#include <functional>
#include <string>
#include "DataStructs.h"
#include "ComponentsH.h"
namespace dae {
	enum SupportedAnimationLoadingTypes{
		PlayerAnim, 
		PookaAnim, 
		FygarAnim, 
		HoseAnim, 
		FireAnim
	};
	struct PlayerAnimationData{
		//Name, ClipId, Initial UvOffset, AmountOfFrames //String is unused, just for clarity / reference
		static const unsigned char AnimationClipCount = 21;
		std::tuple< dae::Vec2, unsigned int,std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(0,0), 1,"IdleRight" },				//0
			{Vec2(384+32,0), 1, "IdleLeft"},			//1
			{Vec2(0,32), 1, "IdleDown"},				//2
			{Vec2(0,64), 1, "IdleUp"},				    //3
			{Vec2(384 + 32,32), 1, "IdleDownFlipped"},	//4
			{Vec2(384 + 32,64), 1, "IdleUpFlipped"},	 //5
			{Vec2(0,0), 2, "WalkingRight"},				//6
			{Vec2(384,0), 2, "WalkingLeft"},			//7
			{Vec2(0,32), 2, "WalkingDown"},				//8
			{Vec2(0,64), 2, "WalkingUp"},				//9
			{Vec2(384,32), 2, "WalkingDownFlipped"},	//10
			{Vec2(384,64), 2, "WalkingUpFlipped"},		//11
			{Vec2(128,0), 2, "Pumping"},				//12
			{Vec2(0,96), 6, "Dying"},					//13
			{Vec2(192, 0), 1, "Winning" },				//14
			{Vec2(128,0), 2, "PumpingRight"},			//15
			{Vec2(256,0), 2, "PumpingLeft"},			//16
			{Vec2(128,32), 2, "PumpingDown"},			//17
			{Vec2(128,64), 2, "PumpingUp"},				//18
			{Vec2(256,32), 2, "PumpingDownFlipped"},	//19
			{Vec2(256,64), 2, "PumpingUpFlipped"}		//20
		};

		
	};
	struct PookaAnimationData {
		//Name, ClipId, Initial UvOffset, AmountOfFrames
		static const unsigned char AnimationClipCount = 8;
		std::tuple< dae::Vec2, unsigned int, std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(32,160), 1,"IdleRight" },				//0
			{Vec2(64,160), 1, "IdleLeft"},				//1
			{Vec2(0,160), 2, "WalkingRight"},			//2
			{Vec2(64,160), 2, "WalkingLeft"},			//3
			{Vec2(128,192), 4, "Inflating"},			//4
			{Vec2(128,96), 1, "Death"},					//5
			{Vec2(128 + 4 * 32,192), 1, "Crushed"},		//5
			{Vec2(64,192),2, "Ghost"}					//6
		};

	};

	struct FygarAnimationData {
		//Name, ClipId, Initial UvOffset, AmountOfFrames
		static const unsigned char AnimationClipCount = 8;
		std::tuple< dae::Vec2, unsigned int, std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(0,128), 1,"IdleRight" },				//0
			{Vec2(64,128), 1, "IdleLeft"},				//1
			{Vec2(0,128), 2, "WalkingRight"},			//2
			{Vec2(64,128), 2, "WalkingLeft"},			//3
			{Vec2(128,160), 4, "Inflating"},			//4
			{Vec2(128,96), 1, "Death"},					//5
			{Vec2(256,160), 1, "Crushed"},				//5
			{Vec2(0,192),2, "Ghost"},					//6
			
		};

	};

	struct HoseAnimationData {
		static const unsigned char AnimationClipCount = 5;
		std::tuple< dae::Vec2, std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(352,128),"FlyRightFull" },
			{Vec2(352,144), "FlyLeftFull" },
			{Vec2(432,96), "FlyUpFull" },
			{Vec2(416,96), "FlyDownFull" }

		};
	};

	struct FireAnimationData {
		static const unsigned char AnimationClipCount = 2;
		std::tuple< dae::Vec2, std::string> AnimationClipData[AnimationClipCount] =
		{
			{Vec2(224,96),"FireRight" },
			{Vec2(160,128), "FireLeft" }

		};
	};
	class AnimationLoader
	{
	public: 
		void LoadAnimation(AnimationComponent * animComp, SupportedAnimationLoadingTypes t)
		{
			PlayerAnimationData Player; 
			PookaAnimationData Pooka; 
			HoseAnimationData Hose;
			FygarAnimationData Fygar;
			FireAnimationData Fire; 

			switch (t)
			{
			case PlayerAnim: 
				
				for (int i = 0; i < Player.AnimationClipCount; i++)
				{
					animComp->CreateAnimation(std::get<0>(Player.AnimationClipData[i]), std::get<1>(Player.AnimationClipData[i]));
				}
				break;
			case PookaAnim:
				for (int i = 0; i < Pooka.AnimationClipCount; i++)
				{
					animComp->CreateAnimation(std::get<0>(Pooka.AnimationClipData[i]), std::get<1>(Pooka.AnimationClipData[i]));
				}
				break;
			case HoseAnim:
					CreateHoseAnimation(animComp,
						std::get<0>(Hose.AnimationClipData[0]),
						std::get<0>(Hose.AnimationClipData[1]),
						std::get<0>(Hose.AnimationClipData[2]),
						std::get<0>(Hose.AnimationClipData[3]));

			case FygarAnim: 
				for (int i = 0; i < Pooka.AnimationClipCount; i++)
				{
					animComp->CreateAnimation(std::get<0>(Fygar.AnimationClipData[i]), std::get<1>(Fygar.AnimationClipData[i]));
				}
				break;

			case FireAnim:
				for (int i = 0; i < Pooka.AnimationClipCount; i++)
				{
					
					CreateFireAnimation(animComp,  std::get<0>(Fire.AnimationClipData[0]), std::get<0>(Fire.AnimationClipData[1]));
				}
				break;

			}
		}
		void CreateFireAnimation(AnimationComponent * animComp, Vec2 uvR, Vec2 uvL)
		{
			int width = 32; 
		
			int height = 32;
			AnimationClip acRight(3, 60U);

			for (int i = 0; i < 2; i++)
				acRight.AddClippedFrame(Vec2(uvR.x + width * i , uvR.y), Vec2(width + width * i, height));
			acRight.AddClippedFrame(Vec2(uvR.x + width * 3, uvR.y), Vec2(width + width * 2, height));
			animComp->m_Animations.push_back(acRight);

			AnimationClip acLeft(3, 60U);
			for (int i = 0; i < 2; i++)
				acLeft.AddClippedFrame(Vec2(uvL.x + width * i, uvL.y), Vec2(width + width * i, height));
			acLeft.AddClippedFrame(Vec2(uvL.x + width * 3, uvL.y), Vec2(width + width * 2, height));
			animComp->m_Animations.push_back(acLeft);
		}
		void CreateHoseAnimation(AnimationComponent * animComp, Vec2 uvR, Vec2 uvL, Vec2 uvB, Vec2 uvT)
		{
			int width = 64;
			int height = 16;
			AnimationClip acRight(64, 1U);

			for (int i = 0; i < width; i++)
				acRight.AddClippedFrame(Vec2(uvR.x + (width - i), uvR.y), Vec2(i, height));
			animComp->m_Animations.push_back(acRight);

			AnimationClip acLeft(64, 1U);
			for (int i = 0; i < width; i++)
				acLeft.AddClippedFrame(Vec2(uvL.x, uvL.y), Vec2(i, height));
			animComp->m_Animations.push_back(acLeft);

			AnimationClip AcBot(64, 1U);
			for (int i = 0; i < width; i++)
				AcBot.AddClippedFrame(Vec2(uvB.x, uvB.y + (width - i)), Vec2(16, i));
			animComp->m_Animations.push_back(AcBot);

			AnimationClip acTop(64, 1U);
			for (int i = 0; i < width; i++)
				acTop.AddClippedFrame(Vec2(uvT.x, uvT.y), Vec2(16, i));
			animComp->m_Animations.push_back(acTop);
			animComp->m_ActiveAnimationId = 0;
		}
	};
}