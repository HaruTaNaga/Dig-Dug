#pragma once
#include <functional>
#include "SDL.h"

namespace dae {
	class cArgs; 
	class  MoveComponent; 
	class AnimationComponent; 
	class PositionComponent; 
	class CollisionComponent; 
	class CommandFactory {
	public: 
		CommandFactory() {};
		~CommandFactory(); 
		std::function<void(cArgs *)> KeyDownP2(SDL_Keycode type);
		std::function<void(cArgs *)> KeyDown(SDL_Keycode type);
		std::function<void(cArgs *)> KeyUp(SDL_Keycode type);
		std::function<void(cArgs *)> MenuKeyDown(SDL_Keycode type);
		std::function<void(cArgs *)> MenuSelected();
		std::function<void(cArgs *)> EmptyLamda();
		std::function<void(cArgs *)> Death(); 
		std::function<void(cArgs *)> Respawn();
		std::function<void(cArgs *)> GameOver();
		std::function<void(cArgs *)> PumpLaunch();
		std::function<void(cArgs *)> PumpEnd();
		std::function<void(cArgs *)> HoseLaunch();
		std::function<void(cArgs *)> HoseEnd();
		std::function<void(cArgs *)> HoseHit();
		std::function<void(cArgs *)> EnemyHit();
		std::function<void(cArgs* )> StartPumpingEnemy();
		std::function<void(cArgs*)> PlayerPumpingEnemy();
		std::function<void(cArgs*)> EnemyPumped();
		std::function<void(cArgs*)> EnemyDeflation();
		std::function<void(cArgs*)> EnemyDeflated();
		std::function<void(cArgs*)> EnemyDeath();
		std::function<void(cArgs*)> EnemyDespawn();
		std::function<void(cArgs*)> EnemyCrushed();

		//
		std::function<void(dae::MoveComponent*, dae::AnimationComponent*)> AiMovement(dae::Orientation dir);
		std::function<void(dae::PositionComponent * pComp, dae::MoveComponent*mComp, dae::AnimationComponent*aComp)> AiStop();
		std::function<void(bool canCollide, dae::CollisionComponent*cComp)> ToggleCollision();
		std::function<void(dae::AnimationComponent*aComp)> AiGhost();
		std::function<void(dae::Vec2 Destination, dae::MoveComponent*mComp, dae::PositionComponent * pComp)> AiGhostMove();
		std::function<void(dae::MoveComponent*mComp)> AiGhostMoveInverseDirection();
	};
}