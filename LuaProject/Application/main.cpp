#include "iostream"
#include <iomanip>
#include <thread>
#include "entt\entt.hpp"
#include <Windows.h>
#include <string>
#include "lua.hpp"

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

void dumpStack(lua_State* L)
{
	int size = lua_gettop(L);
	std::cout << " " << std::string(11, '-');
	std::cout << " STACK BEGIN ";
	std::cout << " " << std::string(11, '-');



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
				value += " . . ";
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

	std::cout << " " << std::string(12, '-');
	std::cout << " STACK END ";
	std::cout << std::string(12, '-') << std::endl;
}

struct Vector3
{
	float X, Y, Z;
	Vector3(float x = 0.f, float y = 0.f, float z = 0.f) : X(x), Y(y), Z(z) {}
};

Vector3 lua_tovector(lua_State* L, int index)
{
	if (!lua_istable(L, index))
	{
		throw "lua_tovector: table expected.";
	}

	Vector3 vector;

	lua_getfield(L, index, "x");
	vector.X = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, index, "y");
	vector.Y = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, index, "z");
	vector.Z = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return vector;
}

void lua_pushvector(lua_State* L, const Vector3& vector)
{
	lua_newtable(L);

	lua_pushnumber(L, vector.X);
	lua_setfield(L, -2, "x");

	lua_pushnumber(L, vector.Y);
	lua_setfield(L, -2, "y");

	lua_pushnumber(L, vector.Z);
	lua_setfield(L, -2, "z");
}

static int RandomVector(lua_State* L)
{
	if (!lua_isnumber(L, 1) || !lua_isnumber(L, 2))
	{
		std::cout << "WRONG\n";
		return 0;
	}

	int min = lua_tonumber(L, 1);
	int max = lua_tonumber(L, 2);
	int diff = max - min;
	lua_pop(L, 2);

	Vector3 vector(rand() % diff + min, rand() % diff + min, rand() % diff + min);
	lua_pushvector(L, vector);
	return 1;
}

static int PrintVector(lua_State* L)
{
	Vector3 vector = lua_tovector(L, 1);
	std::cout << "[C++] Vector (" << vector.X << ", " << vector.Y << ", " << vector.Z << ") " << std::endl;
	return 0;
}

struct Transform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

	Transform(Vector3 position = Vector3(), Vector3 rotation = Vector3(), Vector3 scale = Vector3()) :
		Position(position), Rotation(rotation), Scale(scale) {}
};

Transform lua_totransform(lua_State* L, int index)
{
	if (!lua_istable(L, index))
	{
		throw "lua_totransform: table expected.";
	}

	Transform transform;
	lua_getfield(L, index, "position");
	transform.Position = lua_tovector(L, -1); //EGEN FUNKTION
	lua_getfield(L, index, "rotation");
	transform.Rotation = lua_tovector(L, -1);
	lua_getfield(L, index, "scale");
	transform.Scale = lua_tovector(L, -1);

	return transform;
}

void lua_pushtransform(lua_State* L, const Transform& transform)
{
	lua_newtable(L);

	lua_pushvector(L, transform.Position);
	lua_setfield(L, -2, "position");

	lua_pushvector(L, transform.Rotation);
	lua_setfield(L, -2, "rotation");

	lua_pushvector(L, transform.Scale);
	lua_setfield(L, -2, "scale");
}

static int PrintTransform(lua_State* L)
{
	Transform transform = lua_totransform(L, 1);
	std::cout << "Transform: " << std::endl;

	std::cout << "Position(" << transform.Position.X << ", " << transform.Position.Y << ", " << transform.Position.Z << ")" << std::endl;
	std::cout << "Rotation(" << transform.Rotation.X << ", " << transform.Rotation.Y << ", " << transform.Rotation.Z << ")" << std::endl;
	std::cout << "Scale(" << transform.Scale.X << ", " << transform.Scale.Y << ", " << transform.Scale.Z << ")" << std::endl;

	return 0;
}

static int RandomTransform(lua_State* L)
{
	lua_newtable(L); //Push empty table

	lua_pushvalue(L, 1); //Push copy of argument
	lua_pushvalue(L, 2); //Push copy of argument
	RandomVector(L); //Push random position
	lua_setfield(L, -2, "position"); //Call it position

	lua_pushvalue(L, 1); //Push copy of argument
	lua_pushvalue(L, 2); //Push copy of argument
	RandomVector(L); //Push random rotation
	lua_setfield(L, -2, "rotation"); //Call it rotation

	lua_pushvalue(L, 1); //Push copy of argument
	lua_pushvalue(L, 2); //Push copy of argument
	RandomVector(L); //Push random scale
	lua_setfield(L, -2, "scale"); //Call it scale

	return 1;
}

int main()
{
	entt::registry reg;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";

	//NUMBERS AND VARIABLES
	/*lua_pushnumber(L, 3.14159f);
	lua_setglobal(L, "HEJ");
	lua_pushnumber(L, 1.41421f);
	lua_setglobal(L, "SqrtOfTwo");
	lua_pushnumber(L, 1.61803f);
	lua_setglobal(L, "Phi");
	lua_pushnumber(L, 2.71828f);
	lua_setglobal(L, "Euler");

	luaL_dofile(L, "assLua.lua");
	lua_close(L);
	return 0;*/



	//FAILS part1
	/*std::cout << "Before: " << lua_gettop(L) << std::endl;
	luaL_dofile(L, "fail.lua");
	std::cout << "After: " << lua_gettop(L) << std::endl;
	return 0;*/

	//FAILS part2
	/*lua_pushboolean(L, false);
	lua_pushnil(L);
	lua_pushstring(L, "Hello!");
	lua_pushnumber(L, 3.14159f);
	lua_pushvalue(L, -2);
	dumpStack(L);*/



	//DINOSAURS FUNCTION
	/*if (luaL_dofile(L, "populate.lua") != LUA_OK)
	{
		std::cout << "ERROR: " << lua_tostring(L, -1);
		lua_pop(L, 1);
	}

	lua_getglobal(L, "dino_species");
	std::cout << "[C++] dino_species: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	lua_getglobal(L, "dino_name");
	std::cout << "[C++] dino_name: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	lua_getglobal(L, "dino_wings");
	std::cout << "[C++] dino_wings: " << (lua_tostring(L, -1) ? "true" : "false") << std::endl;
	lua_pop(L, 1);

	lua_getglobal(L, "dino_getnoise");
	lua_pushnumber(L, 7);
	lua_pcall(L, 1, 1, 0);
	std::cout << "[C++] dino noise: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);

	dumpStack(L);
	lua_close(L);
	return 0;*/



	//DINOSAURS TABLE
	//if (luaL_dofile(L, "dino.lua") != LUA_OK)
	//{
	//	std::cout << "ERROR: " << lua_tostring(L, -1);
	//	lua_pop(L, 1);
	//}

	////Push table to stack
	//lua_getglobal(L, "dino");

	//lua_getfield(L, -1, "species");
	//std::cout << "[C++] species: " << lua_tostring(L, -1) << std::endl;
	//lua_pop(L, 1);

	//lua_getfield(L, -1, "name");
	//std::cout << "[C++] name: " << lua_tostring(L, -1) << std::endl;
	//lua_pop(L, 1);

	//lua_getfield(L, -1, "wings");
	//std::cout << "[C++] wings: " << (lua_toboolean(L, -1) ? "true" : "false") << std::endl;
	//lua_pop(L, 1);

	//lua_getfield(L, -1, "getnoise");
	//lua_pushnumber(L, 7);
	//lua_pcall(L, 1, 1, 0);
	//std::cout << "[C++] noise: " << lua_tostring(L, -1) << std::endl;
	//lua_pop(L, 2); //Pop noise and dino table

	//dumpStack(L);
	//lua_close(L);
	//return 0;


	//VECTOR part1
	/*lua_pushcfunction(L, RandomVector);
	lua_setglobal(L, "RandomVector");
	lua_pushcfunction(L, PrintVector);
	lua_setglobal(L, "PrintVector");
	luaL_dofile(L, "vectorTest.lua");*/

	//VECTOR part2 (transform)
	/*lua_pushcfunction(L, RandomTransform);
	lua_setglobal(L, "RandomTransform");
	lua_pushcfunction(L, PrintTransform);
	lua_setglobal(L, "PrintTransform");
	luaL_dofile(L, "transformDemo.lua");*/
	
	luaL_dofile(L, "vector.lua");

	std::thread consoleThread(luaThreadLoop, L);

	while (true)
	{

	}

	return 0;
}