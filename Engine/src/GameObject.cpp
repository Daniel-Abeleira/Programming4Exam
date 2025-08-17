#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace engine
{
	GameObject::~GameObject() {}

	void GameObject::Update(float delta_time)
	{
		for (const auto& component : components)
		{
			component->Update(delta_time);
		}
	}

	void GameObject::Render() const
	{
		for (const auto& component : components)
		{
			component->Render();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (const auto& component : components)
		{
			component->FixedUpdate();
		}
	}

	void GameObject::LateUpdate()
	{
		for (const auto& component : components)
		{
			component->LateUpdate();
		}
	}

	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		component.get()->game_object = this;
		components.push_back(std::move(component));
	}

	Component* GameObject::AddAndGetComponent(std::unique_ptr<Component> component)
	{
		component.get()->game_object = this;
		components.push_back(std::move(component));
		return components.back().get();
	}
}