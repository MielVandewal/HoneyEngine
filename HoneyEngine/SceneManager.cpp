#include "SceneManager.h"
#include "Scene.h"

HoneyEngine::SceneManager::~SceneManager()
{
	for (size_t i{}; i < m_Scenes.size(); ++i)
	{
		SafeDelete(m_Scenes[i]);
	}
}

void HoneyEngine::SceneManager::AddScene(Scene* pScene)
{
	//if there is no scene yet set the first scene you add asactive scene
	if (m_ActiveSceneNr == -1)
		m_ActiveSceneNr = 0;
	m_Scenes.push_back(pScene);
}

//void HoneyEngine::SceneManager::RemoveScene(Scene* pScene)
//{
//	for (size_t i{ 0 }; i < m_Scenes.size(); ++i)
//	{
//		if (m_Scenes[i] == pScene && m_ActiveSceneNr != i)
//		{
//			SafeDelete(m_Scenes[i]);
//			m_Scenes[i] = m_Scenes.back();
//			m_Scenes.pop_back();
//		}
//	}
//}

void HoneyEngine::SceneManager::RemoveScene(const std::string& name)
{
	for (size_t i{ 0 }; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->m_Name == name && m_ActiveSceneNr != i)
		{
			SafeDelete(m_Scenes[i]);
			m_Scenes[i] = m_Scenes.back();
			m_Scenes.pop_back();
		}
	}
}

void HoneyEngine::SceneManager::SetActiveScene(const std::string& name)
{
	for (size_t i{ 0 }; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->m_Name == name)
			m_ActiveSceneNr = i;
	}
}

void HoneyEngine::SceneManager::Update(const float deltaT)
{
	if (m_ActiveSceneNr != -1)
		m_Scenes[m_ActiveSceneNr]->Update(deltaT);
}

void HoneyEngine::SceneManager::FixedUpdate(const float deltaT)
{
	if (m_ActiveSceneNr != -1)
		m_Scenes[m_ActiveSceneNr]->FixedUpdate(deltaT);
}

void HoneyEngine::SceneManager::Render() const
{
	if (m_ActiveSceneNr != -1)
		m_Scenes[m_ActiveSceneNr]->Render();
}
