#pragma once
#include "HoneyEnginePCH.h"
#include "VertexStructs.h"
#include <vector>
#include <string>
#include <fstream>


inline void ParseFile(const std::string& fileName, std::vector<VertexPosNorUV>& vertexBuffer, std::vector<short>& indexBuffer)
{
	std::ifstream file;
	std::string line;
	std::string firstChar;

	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<DirectX::XMFLOAT3> indexes;
	std::vector<DirectX::XMFLOAT3> vertexNormals;
	std::vector<DirectX::XMFLOAT2> textureCoords;

	file.open(fileName, std::ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file, line);
			firstChar = line.substr(0, line.find(' '));
			if (firstChar == "v")
			{
				line = line.substr(3);
				const float posX{ std::stof(line.substr(0, line.find(' '))) };
				line = line.substr(line.find(' ') + 1);
				const float posY{ std::stof(line.substr(0, line.find(' '))) };
				line = line.substr(line.find(' ') + 1);
				const float posZ{ std::stof(line.substr(0)) };
				vertices.push_back(DirectX::XMFLOAT3{ posX, posY, posZ });
			}
			else if (firstChar == "vn")
			{
				line = line.substr(3);
				const float posX{ std::stof(line.substr(0, line.find(' '))) };
				line = line.substr(line.find(' ') + 1);
				const float posY{ std::stof(line.substr(0, line.find(' '))) };
				line = line.substr(line.find(' ') + 1);
				const float posZ{ std::stof(line.substr(0)) };
				vertexNormals.push_back(DirectX::XMFLOAT3{ posX, posY, posZ });
			}
			else if (firstChar == "vt")
			{
				line = line.substr(3);
				const float posX{ std::stof(line.substr(0, line.find(' '))) };
				line = line.substr(line.find(' ') + 1);
				const float posY{ std::stof(line.substr(0, line.find(' '))) };
				textureCoords.push_back(DirectX::XMFLOAT2{ posX, 1 - posY });
			}
			else if (firstChar == "f")
			{
				line = line.substr(1);
				for (int i{}; i < 3; ++i)
				{
					line = line.substr(line.find(' ') + 1);
					size_t vertexIdx{ size_t(std::stoi(line.substr(0, line.find('/')))) };
					line = line.substr(line.find('/') + 1);
					size_t uvIdx{ size_t(std::stoi(line.substr(0, line.find('/')))) };
					line = line.substr(line.find('/') + 1);
					size_t normalIdx{ size_t(std::stoi(line.substr(0, line.find('/')))) };

					VertexPosNorUV vertex{ vertices[vertexIdx - size_t(1)], {}
						, textureCoords[uvIdx - size_t(1)]
						, vertexNormals[normalIdx - size_t(1)]
						,{} };

					//thx bambi for ur help
					bool vertexIsInThere = true;
					for (size_t j{ 0 }; j < vertexBuffer.size(); ++j)
					{
						if (vertex == vertexBuffer[j])
						{
							vertexIsInThere = false;
							indexBuffer.push_back(int(j));
							break;
						}
					}
					if (vertexIsInThere)
					{
						vertexBuffer.push_back(vertex);
						indexBuffer.push_back(int(vertexBuffer.size() - 1));
					}
				}
			}
		}
	}
	file.close();

	//for (uint32_t i{ 0 }; i < indexBuffer.size(); i += 3)
	//{
	//	uint32_t index0 = indexBuffer[i];
	//	uint32_t index1 = indexBuffer[int64_t(i) + 1];
	//	uint32_t index2 = indexBuffer[int64_t(i) + 2];

	//	const DirectX::XMFLOAT3& p0 = vertexBuffer[index0].Position;
	//	const DirectX::XMFLOAT3& p1 = vertexBuffer[index1].Position;
	//	const DirectX::XMFLOAT3& p2 = vertexBuffer[index2].Position;

	//	const DirectX::XMFLOAT2& uv0 = vertexBuffer[index0].UV;
	//	const DirectX::XMFLOAT2& uv1 = vertexBuffer[index1].UV;
	//	const DirectX::XMFLOAT2& uv2 = vertexBuffer[index2].UV;

	//	const DirectX::XMFLOAT3 edge0 = p1 - p0;
	//	const DirectX::XMFLOAT3 edge1 = p2 - p0;

	//	const DirectX::XMFLOAT2 diffX = DirectX::XMFLOAT2(uv1.x - uv0.x, uv2.x - uv0.x);
	//	const DirectX::XMFLOAT2 diffY = DirectX::XMFLOAT2(uv1.y - uv0.y, uv2.y - uv0.y);
	//	float r = 1.f / Cross(diffX, diffY);

	//	DirectX::XMFLOAT3 tangent = (edge0 * diffY.y - edge1 * diffX.x) * r;
	//	vertexBuffer[index0].Tangent += tangent;
	//	vertexBuffer[index1].Tangent += tangent;
	//	vertexBuffer[index2].Tangent += tangent;
	//}
	//for (size_t i{}; i < vertexBuffer.size(); ++i)
	//	vertexBuffer[i].Tangent = GetNormalized(Reject(vertexBuffer[i].Tangent, vertexBuffer[i].Normal));
}
