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

	if (this->layerType != LayerType::Ground &&
		this->layerType != LayerType::UnderLay &&
		this->layerType != LayerType::Overlay)
		return false;
	{
		std::vector<VertexTexture> vertices;
		vertices.emplace_back(glm::vec3(0.5f, 0.5f, 0.0f),
			glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		vertices.emplace_back(glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		vertices.emplace_back(glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
		vertices.emplace_back(glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		Game::VertexBuffers->Set_Data("Plane", vertices);

		std::vector<unsigned int> indices;
		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(3);

		indices.emplace_back(1);
		indices.emplace_back(2);
		indices.emplace_back(3);
		Game::IndexBuffers->Set_Data("Plane", indices);

		Crusty::Engine::VertexLayout vl;
		vl.Push(3);
		vl.Push(2);
		vl.Push(3);

		Game::VertexArrays->Set_Data("Plane", vl);
	}

	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (auto y = 0; y < this->height; y++)
		for (auto x = 0; x < this->width; x++)
			tiles.emplace_back(glm::translate(glm::mat4(1.0f),
				glm::vec3(x * 0.1f, y * 0.1f, 0.0f)) * scale);

	unsigned int instanceVBO = 0;
	glCreateBuffers(1, &instanceVBO);
	Game::VertexArrays->Bind("Plane");

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * tiles.size(), &tiles.front(), GL_STATIC_DRAW);
	const auto tmp = sizeof(glm::mat4) / sizeof(glm::vec4);
	const auto endSize = Game::VertexArrays->Get_Layout("Plane")->Get_Elements().size() + tmp;

	auto offset = 0;

	for (auto i = Game::VertexArrays->Get_Layout("Plane")->Get_Elements().size(); i < endSize; i++)
	{
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(i, tmp, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
			reinterpret_cast<const void*>(offset * sizeof(glm::vec4)));

		glVertexAttribDivisor(i, 1);

		offset++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Game::VertexArrays->UnBind("Plane");

	Game::Shaders->Add("Texture");
	Game::Textures->Add("Grass", "Data/Assets/Textures/Grass.png", 1);

	return true;
}

void Layer::Update(const float& dt)
{
}

void Layer::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
{
	Game::VertexArrays->Bind("Plane");
	Game::VertexBuffers->Bind("Plane");
	Game::Shaders->Load("Texture");
	Game::Shaders->Set_Mat4_On_Active_Shader("uProjection", camera->Get_ProjectionViewMatrix());
	Game::Textures->Load("Grass", 0);
}

void Layer::Render(const float& dt, Crusty::Engine::Camera* camera)
{
	Crusty::Engine::Common::DrawElementsInstanced(
		Game::IndexBuffers->Get_Buffer("Plane"), tiles.size());
}

void Layer::End_Render(const float& dt)
{
	Game::Textures->Unload("Grass");
	Game::Shaders->Unload("Texture");
	Game::VertexBuffers->UnBind("Plane");
	Game::VertexArrays->UnBind("Plane");
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
