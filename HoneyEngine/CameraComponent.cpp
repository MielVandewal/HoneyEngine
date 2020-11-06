#include "CameraComponent.h"
#include "GameContext.h"

HoneyEngine::CameraComponent::CameraComponent() 
	: m_FarPlane(2500.0f)
	, m_NearPlane(0.1f)
	, m_FOV(DirectX::XM_PIDIV4)
	, m_IsActive(true)
{
	XMStoreFloat4x4(&m_Projection, DirectX::XMMatrixIdentity());
	XMStoreFloat4x4(&m_View, DirectX::XMMatrixIdentity());
	XMStoreFloat4x4(&m_ViewInverse, DirectX::XMMatrixIdentity());
	XMStoreFloat4x4(&m_ViewProjection, DirectX::XMMatrixIdentity());
	XMStoreFloat4x4(&m_ViewProjectionInverse, DirectX::XMMatrixIdentity());
}

void HoneyEngine::CameraComponent::Update()
{
	// see https://stackoverflow.com/questions/21688529/binary-directxxmvector-does-not-define-this-operator-or-a-conversion
	using namespace DirectX;
	
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(m_FOV
		, GameContext::GetInstance()->pWindow->GetAspectRatio(), m_NearPlane, m_FarPlane);

	//DirectX::XMVECTOR worldPosition = XMLoadFloat3(&GetTransform()->GetWorldPosition());
	//DirectX::XMVECTOR lookAt = XMLoadFloat3(&GetTransform()->GetForward());
	//DirectX::XMVECTOR upVec = XMLoadFloat3(&GetTransform()->GetUp());

	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(worldPosition, worldPosition + lookAt, upVec);
	//DirectX::XMMATRIX viewInv = XMMatrixInverse(nullptr, view);
	//DirectX::XMMATRIX viewProjectionInv = XMMatrixInverse(nullptr, view * projection);

	//XMStoreFloat4x4(&m_Projection, projection);
	//XMStoreFloat4x4(&m_View, view);
	//XMStoreFloat4x4(&m_ViewInverse, viewInv);
	//XMStoreFloat4x4(&m_ViewProjection, view * projection);
	//XMStoreFloat4x4(&m_ViewProjectionInverse, viewProjectionInv);
}

void HoneyEngine::CameraComponent::Render() const
{
}
