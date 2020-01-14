#include <Crusty.h>

Crusty::Engine::Camera::Camera()
{
}

Crusty::Engine::Camera::Camera(const int& width, const int& height)
{
	this->zNear = -1.0f;
	this->zFar = 1.0f;

	this->Set_Position(0.0f, 0.0f, 0.0f);
	this->Set_Projection(-1.0f, 1.0f, 1.0f, -1.0f);
	this->Update(0.0f);
}

Crusty::Engine::Camera::~Camera()
= default;

void Crusty::Engine::Camera::Set_Position(const float & x, const float & y, const float & z)
{
	this->Set_Position(glm::vec3(x, y, z));
}

void Crusty::Engine::Camera::Set_Position_X(const float & x)
{
	this->position.x += x;
}

void Crusty::Engine::Camera::Set_Position_Y(const float & y)
{
	this->position.y += y;
}

void Crusty::Engine::Camera::Set_Position_Z(const float & z)
{
	this->position.z += z;
}

void Crusty::Engine::Camera::Set_Position(const glm::vec3& pos)
{
	this->position = pos;
}

void Crusty::Engine::Camera::Update(const float& dt)
{
	auto transform = glm::translate(glm::mat4(1.0f), this->Get_Position()) *
		glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));

	auto viewMatrix = glm::inverse(transform);
	this->projView = this->projection * viewMatrix;
}

const float Crusty::Engine::Camera::Get_Near()
{
	return this->zNear;
}

const float Crusty::Engine::Camera::Get_Far()
{
	return this->zFar;
}

void Crusty::Engine::Camera::Set_Near(const float& zNear)
{
	this->zNear = zNear;
}

void Crusty::Engine::Camera::Set_Far(const float& zFar)
{
	this->zFar = zFar;
}

void Crusty::Engine::Camera::Set_Projection(const float & left, const float &right, const float &bottom, const float & top)
{
	this->projection = glm::ortho(left, right, bottom, top, this->zNear, this->zFar);
}

glm::vec3& Crusty::Engine::Camera::Get_Position()
{
	return this->position;
}

void Crusty::Engine::Camera::Render()
{
}

glm::mat4 Crusty::Engine::Camera::Get_ProjectionViewMatrix()
{
	return this->projView;
}
