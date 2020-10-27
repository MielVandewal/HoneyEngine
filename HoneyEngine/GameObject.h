#pragma once
#include "HoneyEnginePCH.h"

namespace HoneyEngine
{
	class BaseComponent;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(const float deltaT);
		void Update(const float deltaT);
		void Render() const;

		void AddComponent(BaseComponent* pComponent);
		template<class T> void RemoveComponent();
		template<class T> T* GetComponent() const;

		bool IsActive() const { return m_IsActive; }
		void SetActive(const bool isActive) { m_IsActive = isActive; }

	private:
		std::vector<BaseComponent*> m_Components;
		bool m_IsActive;
	};
}