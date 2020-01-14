#pragma once
#include <Game.h>

class Map : public ICrustyClient
{
public:
	Map() {}
	explicit Map(const std::string& name, const int& width, const int& height);
	virtual ~Map();
	bool Initialize();
	// Geerbt über ICrustyClient
	virtual void Update(const float & dt) override;
	virtual void Begin_Render(const float & dt, Crusty::Engine::Camera * camera) override;
	virtual void Render(const float & dt, Crusty::Engine::Camera* camera) override;
	virtual void End_Render(const float & dt) override;
	virtual void Add(const std::string& name, const LayerType& layerType);

private:
	std::string name;
	int width;
	int height;
	std::vector<std::shared_ptr<Layer>> Layers;

	// Geerbt über ICrustyClient
	virtual bool Bootstrap() override;
};

