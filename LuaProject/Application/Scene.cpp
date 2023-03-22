#include "Scene.hpp"
#include <iostream>
#include "Components.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (int i = 0; i < m_systems.size(); i++)
	{
		delete m_systems[i];
	}
}

int Scene::GetEntityCount()
{
	return m_registry.alive();
}

int Scene::CreateEntity()
{
	return (int)m_registry.create();
}

bool Scene::IsEntity(int entity)
{
	return m_registry.valid((entt::entity)entity);
}

void Scene::RemoveEntity(int entity)
{
	m_registry.destroy((entt::entity)entity);
}

Scene* Scene::lua_GetSceneUpValue(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = (Scene*)lua_touserdata(L, lua_upvalueindex(1));
	}
	return scene;
}

void Scene::UpdateSystems(float delta)
{
	for (auto it = m_systems.begin(); it != m_systems.end(); it++)
	{
		if ((*it)->OnUpdate(m_registry, delta))
		{
			delete (*it);
			it = m_systems.erase(it);
		}
	}
}

void Scene::lua_openscene(lua_State* L, Scene* scene)
{
	lua_newtable(L);

	luaL_Reg methods[] =
	{
		{"CreateEntity", lua_CreateEntity},
		{"SetComponent", lua_SetComponent},
		{NULL, NULL}
	};

	lua_pushlightuserdata(L, scene);
	luaL_setfuncs(L, methods, 1);
	lua_setglobal(L, "scene");
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	lua_pushnumber(L, scene->CreateEntity());
	return 1;
}

int Scene::lua_SetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "health")
	{
		float value = lua_tonumber(L, 3);
		scene->SetComponent<Health>(entity, value);
		//std::cout << "VALU " << value << "\n";

	}
	else if (type == "poison")
	{
		float tickDamage = lua_tonumber(L, 3);
		//std::cout << "POSSOM " << tickDamage << "\n";
		scene->SetComponent<Poison>(entity, tickDamage);
	}
	else if (type == "behaviour")
	{
		if (scene->HasComponents<Behaviour>(entity))
		{
			scene->RemoveComponent<Behaviour>(entity);
		}

		//Gets the file off the stack
		const char* path = lua_tostring(L, 3);
		luaL_dofile(L, path);

		//luaL_ref pops the value off the stcak so pushvalue adds it again
		lua_pushvalue(L, -1);
		int ref = luaL_ref(L, LUA_REGISTRYINDEX);

		//Populate the behaviour table with information the behaviour should know about
		lua_pushinteger(L, entity);
		lua_setfield(L, -2, "ID");

		lua_pushstring(L, path);
		lua_setfield(L, -2, "path");

		lua_getfield(L, -1, "OnCreate");
		lua_pushvalue(L, -2);
		lua_pcall(L, 1, 0, 0);
	}
	return 1;
}

int Scene::lua_GetEntityCount(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int count = scene->GetEntityCount();
	lua_pushinteger(L, count);
	return 1;
}

int Scene::lua_IsEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	bool alive = scene->IsEntity(entity);
	lua_pushboolean(L, alive);
	return 1;
}

int Scene::lua_RemoveEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	scene->RemoveEntity(entity);
	return 0;
}

int Scene::lua_HasComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	bool hasComponent = false;

	if (type == "health")
	{
		hasComponent = scene->HasComponents<Health>(entity);
	}
	else if (type == "poison")
	{
		hasComponent = scene->HasComponents<Poison>(entity);
	}
	lua_pushboolean(L, hasComponent);
	return 1;
}

int Scene::lua_GetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);

	if (!lua_isinteger(L, 1) || !lua_isstring(L, 2))
	{
		std::cout << "ERROR\n";
		lua_pushnil(L);
		return 1;
	}

	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (!scene->IsEntity(entity))
	{
		lua_pushnil(L);
		return 1;
	}

	if (type == "health" && scene->HasComponents<Health>(entity))
	{
		Health& health = scene->GetComponent<Health>(entity);
		lua_pushnumber(L, health.Value);
		return 1;
	}
	else if (type == "poison" && scene->HasComponents<Poison>(entity))
	{
		Poison& poison = scene->GetComponent<Poison>(entity);
		lua_pushnumber(L, poison.TickDamage);
		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int Scene::lua_RemoveComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "health" && scene->HasComponents<Health>(entity))
	{
		scene->RemoveComponent<Health>(entity);
	}
	else if (type == "poison" && scene->HasComponents<Poison>(entity))
	{
		scene->RemoveComponent<Poison>(entity);
	}
	return 0;
}