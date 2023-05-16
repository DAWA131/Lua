#include "Scene.hpp"

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

void Scene::lua_openscene(lua_State* L, Scene* scene)
{
	lua_newtable(L);

	luaL_Reg methods[] =
	{
		{"GetEntityCount", lua_GetEntityCount},
		{"CreateEntity", lua_CreateEntity},
		{"IsEntity", lua_IsEntity},
		{"RemoveEntity", lua_RemoveEntity},
		{"HasComponent", lua_HasComponent},
		{"GetComponent", lua_GetComponent},
		{"SetComponent", lua_SetComponent},
		{"RemoveComponent", lua_RemoveComponent},
		{"SetPosition", lua_SetPosition},
		{"RemoveTile", lua_RemoveTile},

		{NULL, NULL}
	};

	lua_pushlightuserdata(L, scene);
	luaL_setfuncs(L, methods, 1); // 1 : one upvalue ( lightuserdata )
	
	lua_setglobal(L, "scene");
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

void Scene::UpdateSystems(float delta)
{
	for (auto it = m_systems.begin(); it != m_systems.end();)
	{
		if ((*it)->OnUpdate(m_registry, delta))
		{
			delete (*it);
			it = m_systems.erase(it);
		}
		else
		{
			it++;
		}
	}
}

Scene* Scene::lua_GetSceneUpValue(lua_State* L)
{
	Scene* scene = nullptr;
	if (lua_isuserdata(L, lua_upvalueindex(1)))
	{
		scene = (Scene*)lua_touserdata(L,
			lua_upvalueindex(1));
	}
	return scene;
}

int Scene::lua_GetEntityCount(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	lua_pushinteger(L, scene->GetEntityCount());
	return 1;
}

int Scene::lua_CreateEntity(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	lua_pushnumber(L, scene->CreateEntity());
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
		hasComponent = scene->HasComponents<Health>(entity);
	else if (type == "poison")
		hasComponent = scene->HasComponents<Poison>(entity);
	else if (type == "jump")
		hasComponent = scene->HasComponents<Jumping>(entity);

	lua_pushboolean(L, hasComponent);
	return 1;
}

int Scene::lua_GetComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);

	if (type == "health" && scene->HasComponents<Health>(entity)) {
		Health& health = scene->GetComponent<Health>(entity);
		lua_pushnumber(L, health.Value); // Maybe push a " component " 
		/*	
		lua_newtable(L);

		lua_pushnumber(L, health.Value);
		lua_setfield(L, -2, "health or Value?");
		.. more values for more components
		*/
		return 1;
	}
	else if (type == "poison" && scene->HasComponents<Poison>(entity)) {
		Poison& poison = scene->GetComponent<Poison>(entity);
		lua_pushnumber(L, poison.TickDamage); // Maybe push a " component "
		return 1;
	}

	lua_pushnil(L);
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
	}
	else if (type == "poison")
	{
		float tickDamage = lua_tonumber(L, 3);
		scene->SetComponent<Poison>(entity, tickDamage);
	}
	else if (type == "player")
	{
		scene->SetComponent<Player>(entity);
	}
	else if (type == "drawable")
	{
		std::string texName = lua_tostring(L, 3);
		float x = 0;
		float y = 0;
		if(lua_gettop(L) >= 5)
		{
			x = lua_tonumber(L, 4);
			y = lua_tonumber(L, 5);
		}
		scene->SetComponent<Drawable>(entity, texName, x, y);
	}
	else if (type == "collidable")
	{
		bool coll = lua_toboolean(L, 3);
		scene->SetComponent<Collidable>(entity, coll);
	}
	else if (type == "move")
	{
		float moveX = lua_tonumber(L, 3);
		float moveY = lua_tonumber(L, 4);
		bool setPos = lua_toboolean(L, 5);
		scene->SetComponent<Moving>(entity, moveX, moveY, setPos);
	}
	else if (type == "jump")
	{
		float xSpeed = lua_tonumber(L, 3);
		float ySpeed = lua_tonumber(L, 4);
		scene->SetComponent<Jumping>(entity, xSpeed, -ySpeed);
	}
	else if (type == "stop")
	{
		scene->SetComponent<Stopping>(entity);
	}
	return 0;
}

int Scene::lua_RemoveComponent(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entity = lua_tointeger(L, 1);
	std::string type = lua_tostring(L, 2);
	if (type == "health")
		scene->RemoveComponent<Health>(entity);
	else if (type == "poison")
		scene->RemoveComponent<Poison>(entity);
	else if (type == "move")
		scene->RemoveComponent<Moving>(entity);
	else if (type == "jump")
		scene->RemoveComponent<Jumping>(entity);
	else if (type == "stop")
		scene->RemoveComponent<Stopping>(entity);
	return 0;
}

int Scene::lua_SetPosition(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int entityToMove = lua_tointeger(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);

	auto view = scene->m_registry.view<Drawable>();
	view.each([&](entt::entity entity, Drawable& sprite) {
		if ((int)entity == entityToMove)
		{
			sprite.sprite.setPosition(x,y);
		}
		});
	return 0;
}

int Scene::lua_RemoveTile(lua_State* L)
{
	Scene* scene = lua_GetSceneUpValue(L);
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	x *= 48;
	y *= 48;
	//auto view = scene->m_registry.view<Drawable>(entt::exclude<Player>);
	auto view = scene->m_registry.view<Drawable>(entt::exclude<Player>);
	view.each([&](entt::entity entity, Drawable& sprite) {
			scene->RemoveEntity((int)entity);
		});
	return 0;
}