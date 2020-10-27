#pragma once
namespace HoneyEngine
{
	class BaseComponent
	{
		friend class GameObject;

	public:
		BaseComponent() {};
		virtual ~BaseComponent() {};

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float) {}
		virtual void Render() const {}

	protected:
		GameObject* m_pGameObject = nullptr;
	};
}
