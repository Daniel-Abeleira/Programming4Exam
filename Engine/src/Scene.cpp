#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

engine::Scene::Scene(const std::string& name) : name(name) {}

void engine::Scene::Add(std::shared_ptr<GameObject> object)
{
	objects.emplace_back(std::move(object));
}

void engine::Scene::Remove(std::shared_ptr<GameObject> object)
{
	objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void engine::Scene::RemoveAll()
{
	objects.clear();
}

void engine::Scene::Update(float delta_time)
{
	for (auto& object : objects)
	{
		object->Update(delta_time);
	}
}

void engine::Scene::Render() const
{
	for (const auto& object : objects)
	{
		object->Render();
	}
}

void engine::Scene::FixedUpdate()
{
	for (auto& object : objects)
	{
		object->FixedUpdate();
	}
}

void engine::Scene::LateUpdate()
{
	for (auto& object : objects)
	{
		object->LateUpdate();
	}
}
