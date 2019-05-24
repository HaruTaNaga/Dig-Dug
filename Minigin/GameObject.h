#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "ComponentsH.h"
#include <string.h>
namespace dae
{
	class AnimationComponent; 
	class GameObject final : public SceneObject
	{
	public:
		void Update(const float deltaTime) override;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	
		std::vector<std::shared_ptr<dae::BaseComponent>> mComponentvec;

	private:
		
	public: 
		template <class T>
		T * GetComponent()
		{
			for (auto component : mComponentvec)
				if (typeid(*component.get()) == typeid(T)) { return static_cast<T *>(component.get()); }
			return nullptr;
		}
	};
}
