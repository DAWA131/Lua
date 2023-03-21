#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (int i = 0; i < this->m_systems.size(); i++)
	{
		delete this->m_systems[i];
	}
}

int Scene::getEntityCount()
{
    return this->m_registry.alive();
}

int Scene::createEntity()
{
    return (int)this->m_registry.create();
}

bool Scene::isEntity(int entity)
{
    return this->m_registry.valid((entt::entity)entity);
}

void Scene::removeEntity(int entity)
{
    this->m_registry.destroy((entt::entity)entity);
}

template<typename ...Args>
inline bool Scene::hasComponents(int entity)
{
	return this->m_registry.all_of<Args...>((entt::entity)entity);
}

template<typename T>
inline T& Scene::getComponents(int entity)
{
	return m_registry.get<T>((entt::entity)entity);
}

template<typename T>
inline void Scene::setComponent(int entity, const T& component)
{
	this->m_registry.emplace_or_replace<T>((entt::entity)entity, component);
}

template<typename T, typename ...Args>
inline void Scene::setComponent(int entity, Args ...args)
{
	this->m_registry.emplace_or_replace<T>((entt::entity)entity, args...);
}

template<typename T>
inline void Scene::removeComponent(int entity)
{
	this->m_registry.remove<T>((entt::entity)entity);
}

template<typename T, typename ...Args>
void Scene::CreateSystem(Args ...args)
{
	this->m_systems.emplace_back(new T(args ...));
}


void Scene::UpdateSystems(float delta)
{
	for (auto it = this->m_systems.begin(); it != m_systems.end(); it++)
	{
		 if ((*it)->OnUpdate(m_registry, delta))
		 {
			 delete (*it);
			 it = m_systems.erase(it);
		 }
	}
}