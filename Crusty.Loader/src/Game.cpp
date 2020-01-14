#include <Crusty.h>
#include "Game.h"

Game::Game()
{
	common = std::make_shared<Crusty::Engine::Common>();
	this->Worlds = std::make_shared<World>();

	using namespace std::placeholders;

	common->On_Update = std::bind(&Game::Update, this, _1);
	common->On_BeginRender = std::bind(&Game::Begin_Render, this, _1, _2);
	common->On_Render = std::bind(&Game::Render, this, _1, _2);
	common->On_EndRender = std::bind(&Game::End_Render, this, _1);

	common->On_KeyDown = std::bind(&Game::KeyDown, this, _1, _2);
	common->On_KeyUp = std::bind(&Game::KeyUp, this, _1, _2);
	common->On_Initialized = std::bind(&Game::Initialize, this, _1, _2, _3);
	common->On_MouseButtonDown = std::bind(&Game::MouseButtonDown, this, _1, _2, _3);
	common->On_MouseButtonUp = std::bind(&Game::MouseButtonUp, this, _1, _2, _3);
	common->On_MouseMove = std::bind(&Game::MouseMove, this, _1, _2, _3);
}

Game::~Game()
{
}

bool Game::Bootstrap()
{
	return common->Bootstrap();
}

bool Game::Initialize(const int& width, const int& height, const HWND& hwnd)
{
	return this->Worlds->Bootstrap();
}

void Game::Update(const float& dt)
{
	this->Worlds->Update(dt);
}

void Game::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
{	
	this->Worlds->Begin_Render(dt, camera);
}

void Game::Render(const float& dt, Crusty::Engine::Camera* camera)
{
	this->Worlds->Render(dt, camera);
}

void Game::End_Render(const float& dt)
{
	this->Worlds->End_Render(dt);
}

void Game::KeyDown(const int& key, Crusty::Engine::Camera* camera)
{
	switch (key)
	{
	case 65:
		camera->Set_Position_X(-0.011f);
		break;
	case 68:
		camera->Set_Position_X(+0.011f);
		break;
	case 87:
		camera->Set_Position_Y(-0.011f);
		break;
	case 83:
		camera->Set_Position_Y(+0.011f);
		break;
	case 81:
		camera->Set_Position_Z(+0.011f);
		break;
	case 69:
		camera->Set_Position_Z(-0.011f);
		break;
	default:
		break;
	}

}

void Game::KeyUp(const int& key, Crusty::Engine::Camera* camera)
{
}

int Game::Run()
{
	return this->common->Run();
}

void Game::MouseButtonUp(const int& button, const int& x, const int& y)
{
}

void Game::MouseButtonDown(const int& button, const int& x, const int& y)
{
}

void Game::MouseMove(const int& button, const int& x, const int& y)
{
}
