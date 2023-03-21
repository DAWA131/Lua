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
	for (auto it = m_systems.begin(); it != m_systems.end(); it++)
	{
		if ((*it)->OnUpdate(m_registry, delta))
		{
			delete (*it);
			it = m_systems.erase(it);
		}
	}
}