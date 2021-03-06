#pragma once
#include  "CommandFactory.h"
#include "cArgs.h"
#include "BaseComponent.h"
#include  "GameObject.h"
#include "ComponentsH.h"
namespace dae {
	
	class CommandComponent : public BaseComponent
	{
	public: 
		CommandComponent(GameObject & go);

		void  Empty ();

		void  KeyDown (SDL_Keycode k, PlayerTypes id);
		void  KeyDownMenu(SDL_Keycode k);
		void  KeyDownPlayerOne(SDL_Keycode k);
		void  KeyDownPlayerTwo(SDL_Keycode k);
		void  KeyDownFygar(SDL_Keycode k);
		void  KeyUp (SDL_Keycode type);
		void  KeyUpP2(SDL_Keycode type);
		void  Death (); 
		void  Respawn ();
		void  GameOver (); 

		void  PumpLaunch (); 
		void  PumpEnd ();

		void  HoseLaunch ();
		void  HoseEnd ();
	
		void  HoseHit (GameObject * HitEnemy);
		void  EnemyHit (); 
		void  StartPumpingEnemy ();

		void  PlayerPumping ();
		void  EnemyPumped ();
		void  EnemyDeflate ();

		void  EnemyDeflated ();
		void  EnemyExplode ();
		void  EnemyDespawn ();

		void  EnemyCrushed ();

		void NotifyState(); 
		CommandFactory * m_CommandFactory;
	
		GameObject  & m_Owner; 
		void Update(float deltaTime) override;
		CommandComponent(const CommandComponent& other) = delete;
		CommandComponent(CommandComponent&& other) = delete;
		CommandComponent& operator=(const CommandComponent& other) = delete;
		CommandComponent& operator=(CommandComponent&& other) = delete;
		std::pair<std::function<void(cArgs *)>, cArgs * > m_Pair_Command_Args;
		std::unique_ptr<cArgs> m_cArg;
		StateComponent * m_StateComponent; 
		MoveComponent * m_MoveComponent; 
		AnimationComponent * m_AnimationComponent; 
		DeathComponent * m_DeathComponent; 
		HoseComponent * m_HoseComponent;
		PumpComponent * m_PumpComponent; 
		PositionComponent * m_PositionComponent; 
		MenuComponent * m_MenuComponent; 
		CollisionComponent * m_CollisionComponent; 

		void InitComponents(); 
	};
}