#include "GameObject.h"
#include "BaseComponent.h"

HoneyEngine::GameObject::GameObject()
	: m_IsActive(true)
{
}

HoneyEngine::GameObject::~GameObject()
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		SafeDelete(m_Components[i]);
	}
}

void HoneyEngine::GameObject::FixedUpdate(const float deltaT)
{
	if (!m_IsActive)
		return;
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Update(deltaT);
	}
}

void HoneyEngine::GameObject::Update(const float deltaT)
{
	if (!m_IsActive)
		return;
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Update(deltaT);
	}
}

void HoneyEngine::GameObject::Render() const
{
	if (!m_IsActive)
		return;
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		m_Components[i]->Render();
	}
}

void HoneyEngine::GameObject::AddComponent(BaseComponent* pComponent)
{
	for (size_t i{}; i < m_Components.size(); ++i)
	{
		if (typeid(*m_Components[i]) == typeid(pComponent))
		{
			std::cout << "component is already in this gameobject\n";
			return;
		}
	}
	m_Components.push_back(pComponent);
	pComponent->m_pGameObject = this;
}

template<class T>
void HoneyEngine::GameObject::RemoveComponent()
{
	for (BaseComponent* pComp : m_Components)
	{
		if (typeid(*pComp) == typeid(T))
		{
			delete pComp;
			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), pComp), m_Components.end());
			return;
		}
	}
}

template<class T>
T* HoneyEngine::GameObject::GetComponent() const
{
	const type_info& ti = typeid(T);
	for (BaseComponent* pComp : m_Components)
	{
		if (pComp && typeid(*pComp) == ti)
			return static_cast<T*>(pComp);
	}
	return nullptr;
}
