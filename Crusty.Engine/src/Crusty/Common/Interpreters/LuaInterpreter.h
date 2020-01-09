#pragma once
#include <Crusty.h>

class __declspec(dllexport) LuaInterpreter
{
public:
	LuaInterpreter();
	void LoadAsString(const std::string& str);
	void LoadFile(const std::string& fileName);
	template <class R>
	auto Get_Number(int stackIndex) -> R;
	std::string Get_String(int stackIndex);
	~LuaInterpreter();
private:
	lua_State* state;
};

