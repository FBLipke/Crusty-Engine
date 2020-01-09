#include <Crusty.h>



LuaInterpreter::LuaInterpreter()
{
	this->state = luaL_newstate();
}

void LuaInterpreter::LoadAsString(const std::string& str)
{
	luaL_dostring(this->state, str.c_str());
}

void LuaInterpreter::LoadFile(const std::string& fileName)
{
	luaL_dofile(this->state,fileName.c_str());
}

template <typename R>
auto LuaInterpreter::Get_Number(int stackIndex) -> R
{
	return static_cast<R>(lua_tonumber(this->state, stackIndex));
}

std::string LuaInterpreter::Get_String(int stackIndex)
{
	return std::string(static_cast<const char*>(lua_tostring(this->state, stackIndex)));
}

LuaInterpreter::~LuaInterpreter()
{
	lua_close(this->state);
}
