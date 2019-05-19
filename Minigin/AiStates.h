#pragma once
#include <random>
#include "Map.h"
#define define derp  

#include  "AiComponent.h"
namespace dae {
	class AiComponent; 
	class BaseAiState
	{
	public: 
		BaseAiState() = delete; 
		BaseAiState(AiComponent & Owner) : m_Owner(Owner) {};
		virtual ~BaseAiState() {};
		virtual std::pair<bool, BaseAiState *> Update(float dt) =  0;
		float m_ElapsedTime = 0.0f; 
		AiComponent  & m_Owner; 

	};

	class MovingAiState : public BaseAiState
	{
	public:
		MovingAiState() = delete;
		MovingAiState(AiComponent & owner) : BaseAiState(owner) {};
		~MovingAiState() override {};
		std::pair<bool, dae::BaseAiState *> Update(float dt) override;
		bool m_HasReachedDestination = true; 
	
		Vec2 m_Destination; 
		int m_MoveSpeed; 

	};


	class IdleAiState : public BaseAiState
	{
	public:

		IdleAiState() = delete;
		IdleAiState(AiComponent & owner) : BaseAiState(owner) {};
		~IdleAiState() override {};
		std::pair<bool, BaseAiState *> Update(float dt) override;
		float m_ChanceToGhost = 1.0f / 8.0f;
		float m_ChanceToMove = 1.0f / 2.0f;
		float m_ChanceToFire = 1.0f / 1.0f; 
	};
	class GhostAiState : public BaseAiState
	{
	public:

		GhostAiState() = delete;
		GhostAiState(AiComponent & owner) : BaseAiState(owner) {};
		~GhostAiState() override {};
		std::pair<bool, BaseAiState *> Update(float dt) override;
		bool m_ArrivedAtInaccesibleTile = false; 
		bool m_HasDestination = false; 
		Vec2 m_Destination; 
		float m_PreviousDistance  =  999999; 
	};

	class FireBreathAiState : public BaseAiState {
	public: 
		FireBreathAiState() = delete;
		FireBreathAiState(AiComponent & owner) : BaseAiState(owner) {}; 
		~FireBreathAiState() override {};
		std::pair<bool, BaseAiState *> Update(float dt) override;
		int m_TickCounter = 0;
		
	};
}