#pragma once
#include "ComponentsH.h"
#include "IObserver.h"
namespace dae {
	//class IObserver; 

	class HpUiComponent;  
	class HpComponent : public  BaseComponent {
	public:

		HpComponent(HpUiComponent & m_uicmp,  int hp = 3): m_Hp(hp), m_CurrentHp(hp), m_HpUiComp(m_uicmp) { };
		virtual ~HpComponent() {};
		void Update(float ) override {};
		void NotifyOnDeath();
		bool IsGameOver() { return m_Hp == 0;  }
		int m_CurrentHp; 
		int m_Hp;
		void AddObserver(IObserver * ptr) { m_Observers.push_back(std::make_unique<IObserver>()); m_Observers[m_Observers.size() - 1].reset(ptr); }
		HpUiComponent & m_HpUiComp; 
		std::vector<std::unique_ptr<IObserver>> m_Observers;
	};

}