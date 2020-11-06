#include "TransfromComponent.h"

HoneyEngine::TransfromComponent::TransfromComponent()
	: m_Position(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))
	, m_Rotation(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f))
	, m_Scale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f))
	, m_Forward(DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f))
	, m_Up(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f))
	, m_Right(DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f))
	, m_World()
	, m_HasTransformChanged(false)
{
	XMStoreFloat4x4(&m_World, DirectX::XMMatrixIdentity());
	UpdateTransforms();
}

HoneyEngine::TransfromComponent::~TransfromComponent()
{
}

void HoneyEngine::TransfromComponent::Update()
{
	if (m_HasTransformChanged)
	{
		UpdateTransforms();
		m_HasTransformChanged = false;
	}
}

void HoneyEngine::TransfromComponent::Translate(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Translate(const DirectX::XMFLOAT3& position)
{
	m_Position = position;
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Translate(const DirectX::XMVECTOR& position)
{
	XMStoreFloat3(&m_Position, position);
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Rotate(const float x, const float y, const float z, const bool isEuler)
{
	if (isEuler)
		XMStoreFloat4(&m_Rotation, DirectX::XMQuaternionRotationRollPitchYaw(DirectX::XMConvertToRadians(x),
				DirectX::XMConvertToRadians(y), DirectX::XMConvertToRadians(z)));
	else
		XMStoreFloat4(&m_Rotation, DirectX::XMQuaternionRotationRollPitchYaw(x, y, z));
	m_HasTransformChanged = true;

}

void HoneyEngine::TransfromComponent::Rotate(const DirectX::XMFLOAT3& rotation, const bool isEuler)
{
	if (isEuler)
		XMStoreFloat4(&m_Rotation, DirectX::XMQuaternionRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation.x),
			DirectX::XMConvertToRadians(rotation.y), DirectX::XMConvertToRadians(rotation.z)));
	else
		XMStoreFloat4(&m_Rotation, DirectX::XMQuaternionRotationRollPitchYaw(rotation.x, rotation.x, rotation.z));
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Rotate(const DirectX::XMVECTOR& rotation, const bool isEuler)
{
	if (isEuler)
	{
		DirectX::XMFLOAT4 rot;
		DirectX::XMStoreFloat4(&rot, rotation);
		XMStoreFloat4(&m_Rotation, DirectX::XMQuaternionRotationRollPitchYaw(DirectX::XMConvertToRadians(rot.x),
			DirectX::XMConvertToRadians(rot.y), DirectX::XMConvertToRadians(rot.z)));
	}
	else
		XMStoreFloat4(&m_Rotation, rotation);
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Scale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Scale(const DirectX::XMFLOAT3& scale)
{
	m_Scale = scale;
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::Scale(const DirectX::XMVECTOR& scale)
{
	XMStoreFloat3(&m_Scale, scale);
	m_HasTransformChanged = true;
}

void HoneyEngine::TransfromComponent::UpdateTransforms()
{
}
