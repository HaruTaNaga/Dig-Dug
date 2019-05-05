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
	class GameObject : public SceneObject
	{
	public:
		void Update(const float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		//const std::shared_ptr<dae::BaseComponent> GetComponent(dae::CmpType type);
		union {
			dae::TextureComponent * mTextureCompPtr;
			dae::AnimationComponent * m_AnimationCompPtr;
		};
		dae::PositionComponent * mPositionCompPtr;
	
		std::vector<std::shared_ptr<dae::BaseComponent>> mComponentvec;
		// void AddComponent(std::shared_ptr<BaseComponent>);
		bool IsAnimated = false; 

	private:
		std::string mName; 
		Renderer * m_Renderer; 
		//ServiceLocator m_ServiceLocator;  
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
