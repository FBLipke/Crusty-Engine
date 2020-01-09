#pragma once
#include <Game.h>

class World : public ICrustyClient
{
public:
	World();
	~World();

	void Add(const std::string& name, const int& width, const int& height);

	bool Bootstrap();

	static void CalculateLightByClock();

	// Geerbt über ICrustyClient
	virtual void Update(const float & dt) override;
	virtual void Begin_Render(const float & dt, Crusty::Engine::Camera* camera) override;
	virtual void Render(const float & dt, Crusty::Engine::Camera* camera) override;
	virtual void End_Render(const float & dt) override;

	static float& Get_World_AmbientLight();
	
private:
	
	std::map<std::string, std::shared_ptr<Map>> Maps;
	inline static std::time_t result;
	inline static float ambient;
};

