#pragma once
#include "HoneyEnginePCH.h"
#include "Singleton.h"

namespace HoneyEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		void AddScene(Scene* pScene);
		//void RemoveScene(Scene* pScene); 
		void RemoveScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		Scene* GetActiveScene() { return m_Scenes[m_ActiveSceneNr]; }

		void Update();
		void FixedUpdate();
		void Render() const;

	private:
		std::vector<Scene*> m_Scenes;
		int m_ActiveSceneNr = -1;
	};

}