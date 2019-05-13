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
		std::pair<bool, BaseAiState *> Update(float dt) override {

			m_ElapsedTime += dt;
			if (m_ElapsedTime > 1)
			{
				m_ElapsedTime = 0;
				if (std::rand() % (int)(1 / m_ChanceToMove) == 0)
					return { true, new MovingAiState(m_Owner) };

			}

			return  { false, nullptr };

		};

		float m_ChanceToMove = 1.0f / 4.0f;
	};
}