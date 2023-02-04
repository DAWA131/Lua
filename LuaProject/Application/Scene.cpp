#include"Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

int Scene::GetEntityCount()
{
	return 0;
}

int Scene::CreateEntity()
{
	auto entity = this->m_registry.create();
	this->m_registry.emplace<>(entity);
	return 0;
}

bool Scene::IsEntity(int entity)
{
	return false;
}

void Scene::RemoveEntity(int entity)
{
}
