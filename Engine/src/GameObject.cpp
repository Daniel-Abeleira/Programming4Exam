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
		//const auto& pos = m_transform.GetPosition();
		//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		component.get()->game_object = this;
		components.push_back(std::move(component));
	}
}