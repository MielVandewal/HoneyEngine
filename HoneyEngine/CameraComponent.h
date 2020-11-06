#pragma once
#include "HoneyEnginePCH.h"
#include "BaseComponent.h"

namespace HoneyEngine
{
	class CameraComponent final : public BaseComponent
	{
	public:
		CameraComponent();
		virtual ~CameraComponent() = default;

		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) noexcept = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;

		//setters;
		void SetActive(const bool isActive) { m_IsActive = isActive; }
		void SetFieldOfView(float fov) { m_FOV = fov; }
		void SetNearPlane(float nearPlane) { m_NearPlane = nearPlane; }
		void SetFarPlane(float farPlane) { m_FarPlane = farPlane; }

		//getters
		const float GetFOV() const { return m_FOV; }
		const float GetNearPlane() const { return m_NearPlane; }
		const float GetFarPlane() const { return m_FarPlane; }
		const bool GetIsActive() const { return m_IsActive; }
		const DirectX::XMFLOAT4X4& GetView() const { return m_View; }
		const DirectX::XMFLOAT4X4& GetProjection() const { return m_Projection; }
		const DirectX::XMFLOAT4X4& GetViewInverse() const { return m_ViewInverse; }
		const DirectX::XMFLOAT4X4& GetViewProjection() const { return m_ViewProjection; }
		const DirectX::XMFLOAT4X4& GetViewProjectionInverse() const { return m_ViewProjectionInverse; }

	protected:

	private:
		DirectX::XMFLOAT4X4 m_View;
		DirectX::XMFLOAT4X4 m_Projection;
		DirectX::XMFLOAT4X4 m_ViewInverse;
		DirectX::XMFLOAT4X4 m_ViewProjection;
		DirectX::XMFLOAT4X4 m_ViewProjectionInverse;
		float m_FarPlane;
		float m_NearPlane;
		float m_FOV;
		bool m_IsActive;
	};
}
