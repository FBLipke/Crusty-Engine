#pragma once
#include <Game.h>

class Layer : public ICrustyClient
{
public:
	Layer() {}
	explicit Layer(const std::string& name, const LayerType& layerType, const int& width, const int& height);
	virtual ~Layer();

	bool Initialize();

	// Geerbt über ICrustyClient
	virtual void Update(const float & dt) override;
	virtual void Begin_Render(const float & dt, Crusty::Engine::Camera * camera) override;
	virtual void Render(const float & dt, Crusty::Engine::Camera* camera) override;
	virtual void End_Render(const float & dt) override;

	std::string Get_Name() const;
	std::string Get_Description() const;
	LayerType Get_Type() const;

private:
	std::string name;
	std::string description;

	int width;
	int height;

	LayerType layerType;
	std::vector<glm::mat4> tiles;

	// Geerbt über ICrustyClient
	virtual bool Bootstrap() override;
};

