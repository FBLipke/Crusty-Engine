#include <Game.h>

Layer::Layer(const std::string& name, const LayerType& layerType, const int& width, const int& height)
{
	this->width = width;
	this->height = height;

	this->name = name;
	this->layerType = layerType;
}

Layer::~Layer()
{

}

bool Layer::Initialize()
{
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (auto y = 0; y < this->height; y++)
		for (auto x = 0; x < this->width; x++)
			this->tiles.emplace_back(glm::translate(glm::mat4(1.0f),
				glm::vec3(x * 0.1f, y * 0.1f, 0.0f)) * scale);

	unsigned int instanceVBO = 0;
	glCreateBuffers(1, &instanceVBO);
	Crusty::Engine::Assets::VertexArrays->Bind("Plane");

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->tiles.size(), &this->tiles.front(), GL_STATIC_DRAW);
	const auto tmp = sizeof(glm::mat4) / sizeof(glm::vec4);
	const auto endSize = Crusty::Engine::Assets::VertexArrays->Get_Layout("Plane")->Get_Elements().size() + tmp;

	auto offset = 0;

	auto ElementSize = Crusty::Engine::Assets::VertexArrays->Get_Layout("Plane")->Get_Elements().size();
	for (auto i = ElementSize; i < endSize; i++)
	{
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(i, tmp, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
			reinterpret_cast<const void*>(offset * sizeof(glm::vec4)));

		glVertexAttribDivisor(i, 1);

		offset++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Crusty::Engine::Assets::VertexArrays->UnBind("Plane");

	return true;
}

void Layer::Update(const float& dt)
{
}

void Layer::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
{
	Crusty::Engine::Assets::VertexArrays->Bind("Plane");
	Crusty::Engine::Assets::VertexBuffers->Bind("Plane");
	Crusty::Engine::Assets::Shaders->Load("Texture");
	Crusty::Engine::Assets::Shaders->Set_Mat4_On_Active_Shader("uProjection", camera->Get_ProjectionViewMatrix());
	Crusty::Engine::Assets::Textures->Load("Grass", 0);
}

void Layer::Render(const float& dt, Crusty::Engine::Camera* camera)
{
	Crusty::Engine::Common::DrawElementsInstanced(
		Crusty::Engine::Assets::IndexBuffers->Get_Buffer("Plane"), this->tiles.size());
}

void Layer::End_Render(const float& dt)
{
	Crusty::Engine::Assets::Textures->Unload("Grass");
	Crusty::Engine::Assets::Shaders->Unload("Texture");
	Crusty::Engine::Assets::VertexBuffers->UnBind("Plane");
	Crusty::Engine::Assets::VertexArrays->UnBind("Plane");
}

std::string Layer::Get_Name() const
{
	return this->name;
}

std::string Layer::Get_Description() const
{
	return this->description;
}

LayerType Layer::Get_Type() const
{
	return this->layerType;
}

bool Layer::Bootstrap()
{
	return false;
}
