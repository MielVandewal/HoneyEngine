#pragma once

// Constant buffer used to send MVP matrices to the vertex shader.
struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

// Used to send per-vertex data to the vertex shader.
struct VertexPositionColor
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

struct VertexPosNorUV
{
	VertexPosNorUV(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT2 uv
		, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT3 tangent)
		: Position(std::move(pos))
		, Color(std::move(color))
		, UV(std::move(uv))
		, Normal(std::move(normal))
		, Tangent(std::move(tangent))
	{}

	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Color;
	DirectX::XMFLOAT2 UV;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT3 Tangent;

	bool operator==(const VertexPosNorUV& other) const
	{
		return (other.Position.x == this->Position.x && other.Position.y == this->Position.y
			&& other.Position.y == this->Position.y && other.UV.x == this->UV.x
			&& other.UV.y == this->UV.y && other.Normal.x == this->Normal.x
			&& other.Normal.y == this->Normal.y && other.Normal.z == this->Normal.z);
	}
};