#pragma once
#include "BaseComponent.h"

namespace  dae {
	class TextComponent;
	class TextureComponent;


	class ScoreUiComponent : public BaseComponent
	{

	public:
		ScoreUiComponent(TextComponent & texc);


		virtual ~ScoreUiComponent() {};

		ScoreUiComponent(const ScoreUiComponent& other) = delete;
		ScoreUiComponent(ScoreUiComponent&& other) = delete;
		ScoreUiComponent& operator=(const ScoreUiComponent& other) = delete;
		ScoreUiComponent& operator=(ScoreUiComponent&& other) = delete;
		void Score(int amount = 0);
		int m_Score;
		TextComponent & m_TextComponent;


	};

}
