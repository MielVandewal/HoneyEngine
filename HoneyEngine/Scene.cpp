#include "Scene.h"
#include "GameObject.h"

HoneyEngine::Scene::Scene(const std::string& name) 
	: m_Name(name) 
{
}

HoneyEngine::Scene::~Scene()
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		SafeDelete(m_Objects[i]);
	}
}

void HoneyEngine::Scene::AddGameObject(GameObject* object)
{
	m_Objects.push_back(object);
}

void HoneyEngine::Scene::RemoveGameObject(GameObject* pObject)
{
	for (size_t i{ 0 }; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i] == pObject)
		{
			SafeDelete(m_Objects[i]); 
			m_Objects[i] = m_Objects.back();
			m_Objects.pop_back();
		}
	}
}

void HoneyEngine::Scene::Update(const float deltaT)
{
	for (GameObject* gameObject : m_Objects)
	{
		gameObject->Update(deltaT);
	}
}

void HoneyEngine::Scene::FixedUpdate(const float deltaT)
{
	for (GameObject* gameObject : m_Objects)
	{
		gameObject->FixedUpdate(deltaT);
	}
}

void HoneyEngine::Scene::Render() const
{
	for (const GameObject* gameObject : m_Objects)
	{
		gameObject->Render();
	}
}