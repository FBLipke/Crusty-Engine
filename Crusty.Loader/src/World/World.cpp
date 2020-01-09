#define _CRT_SECURE_NO_WARNINGS
#include <Game.h>

World::World()
{


}

World::~World()
{

}

void World::Add(const std::string& name, const int& width, const int& height)
{
	this->Maps.emplace(name, std::make_shared<Map>(name, width, height));
}

bool World::Bootstrap()
{
	Add("Untitled", 100, 100);

	for (const auto& map : this->Maps)
		map.second->Initialize();

	return true;
}

void World::CalculateLightByClock()
{
	ambient = 1.0f;
	
	switch (std::localtime(&World::result)->tm_hour)
	{
	case 8:
	case 16:
		ambient = 0.9f;
		break;
	case 7:
	case 17:
		ambient = 0.8f;
		break;
	case 6:
	case 18:
		ambient = 0.7f;
		break;
	case 5:
	case 19:
		ambient = 0.6f;
		break;
	case 4:
	case 20:
		ambient = 0.5f;
		break;
	case 3:
	case 21:
		ambient = 0.4f;
		break;
	case 2:
	case 22:
		ambient = 0.3f;
		break;
	case 1:
	case 23:
		ambient = 0.2f;
		break;
	case 0:
		ambient = 0.1f;
		break;
	}
}

void World::Update(const float & dt)
{
	World::CalculateLightByClock();

	for (const auto& map : this->Maps)
		map.second->Update(dt);
}

void World::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
{
	for (const auto& map : this->Maps)
		map.second->Begin_Render(dt, camera);
}

void World::Render(const float & dt, Crusty::Engine::Camera* camera)
{
	for (const auto& map : this->Maps)
		map.second->Render(dt, camera);
}

void World::End_Render(const float& dt)
{
	for (const auto& map : this->Maps)
		map.second->End_Render(dt);
}

float & World::Get_World_AmbientLight()
{
	return ambient;
}
