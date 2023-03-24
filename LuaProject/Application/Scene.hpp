#include "entt\entt.hpp"
#include "lua.hpp"
#include <cstring>

struct Health
{
	float Value;
};

struct Poison
{
	float TickDamage;
};

struct Behaviour
{
	char ScriptPath[64];
	int LuaTableRef;

	Behaviour(const char* path, int luaRef) : LuaTableRef(luaRef)
	{
		memset(ScriptPath, '\0', 64);
		strcpy_s(ScriptPath, path);
	}
};






class System
{
public:
	virtual bool OnUpdate(entt::registry& registry, float delta) = 0;
};

class PoisonSystem : public System
{
	int m_lifetime;

public:
	PoisonSystem(int lifetime) : m_lifetime(lifetime) {}

	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Health, Poison>();
		view.each([](Health& health, const Poison& poison)
			{
				health.Value -= poison.TickDamage;
			});

		return (--m_lifetime) <= 0;
	}
};

class CleanupSystem : public System
{
public:
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Health>();
		view.each([&](entt::entity entity, const Health& health)
			{
				if (health.Value <= 0.f)
				{
					registry.destroy(entity);
				}
			});

		return false;
	}
};

class InfoSystem : public System
{
	int m_updateCounter = 0;

public:

	InfoSystem() = default;
	bool OnUpdate(entt::registry& registry, float delta) final
	{
		int count = registry.alive();
		auto healthView = registry.view<Health>();
		auto poisonView = registry.view<Poison>();
		printf("\n-- Update %i --\n", ++m_updateCounter);
		printf(" Living entities:\t%i\n", healthView.size());
		printf(" Poisoned entities:\t%i\n", poisonView.size());
		return false;
	}
};

class BehaviourSystem : public System
{
	lua_State* L;

public:
	BehaviourSystem(lua_State* L) : L(L) {}

	bool OnUpdate(entt::registry& registry, float delta) final
	{
		auto view = registry.view<Behaviour>();
		view.each([&](Behaviour& script)
			{
				lua_rawgeti(L, LUA_REGISTRYINDEX, script.LuaTableRef);
				lua_getfield(L, -1, "OnUpdate");
				lua_pushvalue(L, -2);
				lua_pushnumber(L, delta);

				if (lua_pcall(L, 1, 0, 0) != LUA_OK)
				{
				}

				lua_pop(L, 1);
			});

		return false;
	}
};






class Scene
{
	entt::registry m_registry;
	std::vector<System*> m_systems;
	lua_State* L;

public:
	Scene(lua_State* L);
	~Scene();

	int GetEntityCount();
	int CreateEntity();
	bool IsEntity(int entity);
	void RemoveEntity(int entity);




	template<typename...Args>
	bool HasComponents(int entity);

	template<typename T>
	T& GetComponent(int entity);

	template<typename T>
	void SetComponent(int entity, const T& component);

	template<typename T, typename...Args>
	void SetComponent(int entity, Args...args);

	template<typename T>
	void RemoveComponent(int entity);



	template<typename T, typename...Args>
	void CreateSystem(Args...args);
	void UpdateSystems(float delta);



	static void lua_openscene(lua_State* L, Scene* scene);

private:
	static Scene* lua_GetSceneUpValue(lua_State* L);
	static int lua_CreateEntity(lua_State* L);
	static int lua_SetComponent(lua_State* L);



	static int lua_GetEntityCount(lua_State* L);
	static int lua_IsEntity(lua_State* L);
	static int lua_RemoveEntity(lua_State* L);
	static int lua_HasComponent(lua_State* L);
	static int lua_GetComponent(lua_State* L);
	static int lua_RemoveComponent(lua_State* L);

};






template<typename ...Args>
inline bool Scene::HasComponents(int entity)
{
	return m_registry.all_of<Args...>((entt::entity)entity);
}

template<typename T>
inline T& Scene::GetComponent(int entity)
{
	return m_registry.get<T>((entt::entity)entity);
}

template<typename T>
inline void Scene::SetComponent(int entity, const T& component)
{
	m_registry.emplace_or_replace<T>((entt::entity)entity, component);
}

template<typename T, typename ...Args>
inline void Scene::SetComponent(int entity, Args ...args)
{
	m_registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template<typename T>
inline void Scene::RemoveComponent(int entity)
{
	m_registry.remove<T>((entt::entity)entity);
}

template<typename T, typename ...Args>
inline void Scene::CreateSystem(Args ...args)
{
	m_systems.emplace_back(new T(args...));
}