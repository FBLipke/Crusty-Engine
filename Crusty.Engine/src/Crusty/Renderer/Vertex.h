#pragma once
#include <Crusty.h>

struct __declspec(dllexport) VertexTexture
{
	glm::vec3 Position{};
	glm::vec2 TexCoord{};
	glm::vec3 Color{};

	VertexTexture(const glm::vec3& pos, const glm::vec2& texcoord, const glm::vec3& color)
	{
		this->Color = color;
		this->Position = pos;
		this->TexCoord = texcoord;
	}

	VertexTexture(const glm::vec3& pos, const glm::vec2& texcoord)
	{
		this->Position = pos;
		this->TexCoord = texcoord;
	}

	VertexTexture() {}
};

struct __declspec(dllexport) VertexColor
{
	glm::vec3 Position{};
	glm::vec3 Color{};

	VertexColor(const glm::vec3& pos, const glm::vec3& color)
	{
		this->Position = pos;
		this->Color = color;
	}
};
