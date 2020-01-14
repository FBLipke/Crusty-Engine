#include <Game.h>

Map::Map(const std::string& name, const int& width, const int& height)
{
	this->name = name;
	this->height = height;
	this->width = width;
	
}

Map::~Map()
{
	this->Layers.clear();
}

bool Map::Initialize()
{
	Add("GroundLayer", Ground);

	for (auto& layer : this->Layers)
		layer->Initialize();

	return true;
}

void Map::Update(const float& dt)
{
	for (auto& layer : this->Layers)
		layer->Update(dt);
}

void Map::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
{
	for (auto& layer : this->Layers)
		layer->Begin_Render(dt,camera);
}

void Map::Render(const float& dt, Crusty::Engine::Camera* camera)
{
	for (auto& layer : this->Layers)
		layer->Render(dt, camera);
}

void Map::End_Render(const float& dt)
{
	for (auto& layer : this->Layers)
		layer->End_Render(dt);
}

void Map::Add(const std::string& name, const LayerType& layerType)
{
	this->Layers.emplace_back(std::make_shared<Layer>(name, layerType, this->width, this->height));
}

bool Map::Bootstrap()
{
	return false;
}
