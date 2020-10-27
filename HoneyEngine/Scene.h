#pragma once
#include "HoneyEnginePCH.h"
#include "SceneManager.h"

namespace HoneyEngine
{
	class GameObject;

	class Scene
	{
		friend class SceneManager;

	public:
		Scene(const std::string& name);
		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void AddGameObject(GameObject* object);
		void RemoveGameObject(GameObject* object = nullptr);

		void Update(const float deltaT);
		void FixedUpdate(const float deltaT);
		void Render() const;

	private:
		std::vector<GameObject*> m_Objects;
		std::string m_Name;
	};
}