#include "iostream"
#include <thread>
#include "entt\entt.hpp"
#include <Windows.h>
#include <string>
#include "lua.hpp"
#include <iomanip>
#include <cassert>
//#include "lua/M2main.cpp"

void dumpError(lua_State* L)
{
	if (lua_gettop(L) && lua_isstring(L, -1))
	{
		std::cout << "LUA Error: " << lua_tostring(L, -1) << "\n";
		lua_pop(L, 1);
	}
}

void luaThreadLoop(lua_State* L)
{
	std::string input;
	while (GetConsoleWindow())
	{
		std::cout << "-> ";
		std::getline(std::cin, input);

		if (luaL_dostring(L, input.c_str()) != LUA_OK)
		{
			dumpError(L);
		}
	}
}

void doLuaFile(lua_State* L, const std::string& file)
{
	if(luaL_dofile(L, file.c_str()))
	{
		dumpError(L);
	}
}

void DumpStack(lua_State* L)
{
	int size = lua_gettop(L);

	std::cout << " " << std::string(11, ' - ');
	std::cout << " STACK BEGIN ";
	std::cout << std::string(11, ' - ') << std::endl;

	for (int i = size; i > 0; i--)
	{
		int type = lua_type(L, i);
		std::string typeName = lua_typename(L, type);
		std::string value;

		if (type == LUA_TSTRING)
		{
			value = "\"";
			value += lua_tostring(L, i);

			if (value.size() > 11)
			{
				value.resize(9);
				value += "..";
			}

			value += "\"";
		}
		else if (type == LUA_TBOOLEAN)
		{
			value = lua_toboolean(L, i) ? "true" : "false";
		}
		else if (type == LUA_TNIL)
		{
			value = "nil";
		}
		else if (lua_isnumber(L, i))
		{
			value = std::to_string(lua_tonumber(L, i));
		}
		else if (lua_isstring(L, i))
		{
			value = lua_tostring(L, i);
		}

		std::cout << std::setw(3) << i << " | ";
		std::cout << typeName << std::setw(25 - typeName.size()) << value;
		std::cout << std::setw(5 - typeName.size() - value.size()) << " | ";
		std::cout << std::setw(2) << -(size - i + 1);
		std::cout << std::endl;
	}

	std::cout << " " << std::string(12, ' - ');
	std::cout << " STACK END ";
	std::cout << std::string(12, ' - ') << std::endl;
}

struct vector3
{
	float X, Y, Z;
	vector3(float x = 0.f, float y = 0.f, float z = 0.f)
		:X(x), Y(y), Z(z) {}
};

struct transform
{
	vector3 p, r, s;
	transform(vector3 p, vector3 r, vector3 s)
		:p(p), r(r), s(s) {}
	transform()
		:p(vector3()), r(vector3()), s(vector3()) {}
};

vector3 lua_tovector(lua_State* L, int i)
{
	if (!lua_istable(L, i))
	{
		assert("Inxex isnt table!");
	}
	vector3 ret;

	lua_getfield(L, i, "X");
	ret.X = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, i, "Y");
	ret.Y = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, i, "Z");
	ret.Z = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return ret;
}

transform lua_totransform(lua_State* L, int i)
{
	if (!lua_istable(L, i))
	{
		assert("Inxex isnt table!");
	}
	transform ret;
	vector3 temp;

	lua_getfield(L, i, "position");
	ret.p = lua_tovector(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, i, "rotation");
	ret.r = lua_tovector(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, i, "scale");
	ret.s = lua_tovector(L, -1);
	lua_pop(L, 1);

	return ret;
}

static int PrintVector(lua_State* L)
{
	vector3 vector = lua_tovector(L, 1);

	std::cout << "[C++] Vector(" << vector.X << ", " << vector.Y << ", " << vector.Z << ")\n";

	return 0;
}

static int PrintTransform(lua_State* L)
{
	transform worldMatrix = lua_totransform(L, 1);

	std::cout << "[C++] Matrix:\n" <<
		"Pos(" << worldMatrix.p.X << ", " << worldMatrix.p.Y << ", " << worldMatrix.p.Z << ")\n" <<
		"rot(" << worldMatrix.r.X << ", " << worldMatrix.r.Y << ", " << worldMatrix.r.Z << ")\n" <<
		"scale(" << worldMatrix.s.X << ", " << worldMatrix.s.Y << ", " << worldMatrix.s.Z << ")\n";

	return 0;
}

void lua_pushvector(lua_State* L, const vector3& vec)
{
	lua_newtable(L);

	lua_pushnumber(L, vec.X);
	lua_setfield(L, -2, "X");

	lua_pushnumber(L, vec.Y);
	lua_setfield(L, -2, "Y");

	lua_pushnumber(L, vec.Z);
	lua_setfield(L, -2, "Z");
}

void lua_pushtransform(lua_State* L, const transform& matrix)
{
	lua_newtable(L);

	lua_pushvector(L, matrix.p);
	lua_setfield(L, -2, "position");

	lua_pushvector(L, matrix.r);
	lua_setfield(L, -2, "rotation");

	lua_pushvector(L, matrix.s);
	lua_setfield(L, -2, "scale");
}

static int RandomVector(lua_State* L)
{
	if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
	{
		assert("Invalid input");
		return 0;
	}

	int min = lua_tonumber(L, 1);
	int max = lua_tonumber(L, 2);
	int diff = max - min;
	lua_pop(L, 2);

	vector3 vec((rand() % diff + min), (rand() % diff + min), (rand() % diff + min));
	lua_pushvector(L, vec);
	return 1;
}

static int RandomTransformation(lua_State* L)
{
	lua_newtable(L);

	lua_pushnumber(L, 1);
	lua_pushnumber(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "position");

	lua_pushnumber(L, 1);
	lua_pushnumber(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "rotation");

	lua_pushnumber(L, 1);
	lua_pushnumber(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "scale");
	return 1;
}

int main()
{

	entt::registry reg;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";

	std::thread consoleThread(luaThreadLoop, L);

	//doLuaFile(L, "lua/vector.lua");

	//lua_pushcfunction(L, PrintVector);
	//lua_setglobal(L, "PrintVector");

	//lua_pushcfunction(L, PrintTransform);
	//lua_setglobal(L, "PrintTransform");

	//lua_pushcfunction(L, RandomVector);
	//lua_setglobal(L, "RandomVector");

	//lua_pushcfunction(L, RandomTransformation);
	//lua_setglobal(L, "RandomTransformation");

	//doLuaFile(L, "lua/transformDemo.lua");

	int bp = 2;
	while (true)
	{
		//return 0;
		//run game here
	}

	return 0;
}