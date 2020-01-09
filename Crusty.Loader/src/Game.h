#pragma once
#include <Crusty.h>

#include <World/Map/Layer.h>
#include <World/Map/Map.h>
#include <World/World.h>

class Game : public ICrustyClient
{
public:
	Game();
	~Game();
	bool Bootstrap();
	bool Initialize(const int& width, const int& height, const HWND& hwnd);

	void Update(const float& dt) override;
	void Begin_Render(const float& dt, Crusty::Engine::Camera* camera) override;
	void Render(const float& dt, Crusty::Engine::Camera* camera) override;
	void End_Render(const float& dt) override;

	void KeyDown(const int& key, Crusty::Engine::Camera* camera);
	void KeyUp(const int& key, Crusty::Engine::Camera* camera);

	int Run();
	void MouseButtonUp(const int& button, const int& x, const int& y);
	void MouseButtonDown(const int& button, const int& x, const int& y);
	void MouseMove(const int& button, const int& x, const int& y);

	static std::shared_ptr<Crusty::Engine::TextureManager> Textures;
	static std::shared_ptr<Crusty::Engine::VertexBufferManager> VertexBuffers;
	static std::shared_ptr<Crusty::Engine::IndexBufferManager> IndexBuffers;
	static std::shared_ptr<Crusty::Engine::VertexArrayManager> VertexArrays;
	static std::shared_ptr<Crusty::Engine::ShaderManager> Shaders;
	

	std::shared_ptr<World> Worlds;
private:
	std::shared_ptr<Crusty::Engine::Common> common;
};

