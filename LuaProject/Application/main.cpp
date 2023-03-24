#include <iostream>
#include <thread>
#include <string>
#include <iomanip>
#include <cassert>
#include "Scene.hpp"
//#include "lua/M2main.cpp"
#include <Windows.h>

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

std::string GetValueString(lua_State* L, int i)
{
	switch (lua_type(L, i))
	{
	case LUA_TNIL: return "nil";
	case LUA_TBOOLEAN:
		return lua_toboolean(L, i) ? "true" : "false";
	case LUA_TNUMBER: return std::to_string(lua_tonumber(L, i));
	case LUA_TSTRING: return lua_tostring(L, i);
	default: return "";
	}
}

void DumpStack(lua_State* L)
{
	int size = lua_gettop(L);

	std::cout << "--- STACK BEGIN ---" << std::endl;
	for (int i = size; i > 0; i--)
	{
		std::cout << i
			<< "\t"
			<< lua_typename(L, lua_type(L, i))
			<< "\t\t" << GetValueString(L, i)
			<< std::endl;
	}
	std::cout << "---- STACK END ----" << std::endl;
}

struct Vector3
{
	float X, Y, Z;
	Vector3(float x = 0.f, float y = 0.f, float z = 0.f) :
		X(x), Y(y), Z(z) {}
};

Vector3 lua_tovector(lua_State* L, int index)
{
	if (!lua_istable(L, index))
	{
		throw "lua_tovector: table expected";
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

static int PrintVector(lua_State* L)
{
	Vector3 vector = lua_tovector(L, 1); //Own function

	std::cout << "[C++] Vector("
		<< vector.X << ", "
		<< vector.Y << ", "
		<< vector.Z << ")"
		<< std::endl;

	return 0;
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

struct Transform
{
	Vector3 Position, Rotation, Scale;
	Transform(Vector3 position = Vector3(), Vector3 rotation = Vector3(), Vector3 scale = Vector3()) :
		Position(position), Rotation(rotation), Scale(scale) {}
};

Transform lua_totransform(lua_State* L, int index)
{
	if (!lua_istable(L, index))
	{
		throw "lua_totransform: table expected";
	}

	Transform transform;

	lua_getfield(L, index, "position");
	transform.Position = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, index, "rotation");
	transform.Rotation = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, index, "scale");
	transform.Scale = lua_tonumber(L, -1);
	lua_pop(L, 1);

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
	Transform transform = lua_totransform(L, 1); //Own function

	std::cout << "[C++] Transform:" << std::endl;

	std::cout << "Position("
		<< transform.Position.X << ", "
		<< transform.Position.Y << ", "
		<< transform.Position.Z << ")"
		<< std::endl;

	std::cout << "Rotation("
		<< transform.Rotation.X << ", "
		<< transform.Rotation.Y << ", "
		<< transform.Rotation.Z << ")"
		<< std::endl;

	std::cout << "Scale("
		<< transform.Scale.X << ", "
		<< transform.Scale.Y << ", "
		<< transform.Scale.Z << ")"
		<< std::endl;

	return 0;
}

static int RandomTransform(lua_State* L)
{
	lua_newtable(L);

	lua_pushvalue(L, 1);
	lua_pushvalue(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "position");

	lua_pushvalue(L, 1);
	lua_pushvalue(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "rotation");

	lua_pushvalue(L, 1);
	lua_pushvalue(L, 2);
	RandomVector(L);
	lua_setfield(L, -2, "scale");

	return 1;
}

int main()
{
	entt::registry registry;
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::cout << "Hello from c++" << "\n";

	//DINO
	/*luaL_dofile(L, "populate.lua");
	lua_getglobal(L, "dino");
	lua_getfield(L, -1, "species");
	std::cout << "Species: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);
	lua_getfield(L, -1, "name");
	std::cout << "Name: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);
	lua_getfield(L, -1, "wings");
	std::cout << "Wings: " << (lua_toboolean(L, -1) ? "true" : "false") << std::endl;
	lua_pop(L, 1);
	lua_getfield(L, -1, "getnoise");
	lua_pushnumber(L, 7);
	lua_pcall(L, 1, 1, 0);
	std::cout << "Noise: " << lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);*/


	srand(time(NULL));
	/*for (int i = 0; i < 100; i++)
	{
		auto entity = registry.create();
		registry.emplace<Health>(entity, 100.f);
		float tickDamage = rand() % 10 + 1;
		registry.emplace<Poison>(entity, tickDamage);
	}*/

	//int iterations = 0;
	//while (registry.alive())
	//{
	//	//PoisonSystem
	//	{
	//		auto view = registry.view<Health, Poison>();
	//		view.each([](Health& health, const Poison& poison)
	//			{
	//				health.Value -= poison.TickDamage;
	//			});
	//	}

	//	//CleanupSystem
	//	{
	//		auto view = registry.view<Health>();
	//		view.each([&](entt::entity entity, const Health& health)
	//			{
	//				if (health.Value <= 0.f)
	//				{
	//					registry.destroy(entity);
	//				}
	//			});
	//	}

	//	//CureSystem
	//	{
	//		if ((rand() % 20) == 0)
	//		{
	//			auto view = registry.view<Poison>();
	//			view.each([&](entt::entity entity, const Poison& poison)
	//				{
	//					registry.remove<Poison>(entity);
	//				});
	//			std::cout << "Cured all entities!" << std::endl;
	//		}
	//	}

	//	//SpawnpoisonSystem
	//	{
	//		auto view = registry.view<Health>(entt::exclude<Poison>);
	//		view.each([&](entt::entity entity, const Health& health)
	//			{
	//				if ((rand() % 4) == 0)
	//				{
	//					float damage = rand() % 10 + 1;
	//					registry.emplace<Poison>(entity, damage);
	//					std::cout << "Poisoned entity " << (int)entity << std::endl;
	//				}
	//			});
	//	}

	//	iterations++;
	//	std::cout << "Iteration " << iterations << ", entities alive: " << registry.alive() << std::endl;
	//}


	Scene scene(L);
	Scene::lua_openscene(L, &scene);

	scene.CreateSystem<PoisonSystem>(100);
	scene.CreateSystem<CleanupSystem>();
	scene.CreateSystem<InfoSystem>();
	luaL_dofile(L, "sceneDemo.lua");

	for (int i = 0; i < 100; i++)
	{
		scene.UpdateSystems(1); //Change to delta
	}


	std::thread consoleThread(luaThreadLoop, L);
	
	while (true)
	{

	}
	return 0;
}