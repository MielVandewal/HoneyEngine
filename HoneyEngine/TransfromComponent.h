#pragma once
#include "HoneyEnginePCH.h"
#include "BaseComponent.h"

namespace HoneyEngine
{
	class TransfromComponent final : public BaseComponent
	{
	public:
		TransfromComponent();
		~TransfromComponent();

		TransfromComponent(const TransfromComponent& other) = delete;
		TransfromComponent(TransfromComponent&& other) = delete;
		TransfromComponent& operator=(const TransfromComponent& other) = delete;
		TransfromComponent& operator=(TransfromComponent&& other) = delete;

		void Update() override;

		void Translate(const float x, const float y, const float z);
		void Translate(const DirectX::XMFLOAT3& position);
		void Translate(const DirectX::XMVECTOR& position);

		void Rotate(const float x, const float y, const float z, const bool isEuler = true);
		void Rotate(const DirectX::XMFLOAT3& position, const bool isEuler = true);
		void Rotate(const DirectX::XMVECTOR& position, const bool isEuler = true);

		void Scale(const float x, const float y, const float z);
		void Scale(const DirectX::XMFLOAT3& position);
		void Scale(const DirectX::XMVECTOR& position);

		const DirectX::XMFLOAT3& GetPosition() const { return m_Position; }
		const DirectX::XMFLOAT4& GetRotation() const { return m_Rotation; }
		const DirectX::XMFLOAT3& GetScale() const { return m_Scale; }
		const DirectX::XMFLOAT3& GetForward() const { return m_Forward; }
		const DirectX::XMFLOAT3& GetUp() const { return m_Up; }
		const DirectX::XMFLOAT3& GetRight() const { return m_Right; }
		const DirectX::XMFLOAT4X4& GetWorld() const { return m_World; }

	private:
		void UpdateTransforms();

		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT4 m_Rotation;
		DirectX::XMFLOAT3 m_Scale;

		DirectX::XMFLOAT3 m_Forward;
		DirectX::XMFLOAT3 m_Up;
		DirectX::XMFLOAT3 m_Right;

		DirectX::XMFLOAT4X4 m_World;
		bool m_HasTransformChanged;
	};
}