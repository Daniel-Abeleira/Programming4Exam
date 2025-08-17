#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include "Transform.h"
#include "Component.h"

namespace engine
{
	class GameObject final
	{
	public:
		virtual void Update(float delta_time);
		virtual void Render() const; 
		virtual void LateUpdate();
		virtual void FixedUpdate();

		void AddComponent(std::unique_ptr<Component> component);
		Component* AddAndGetComponent(std::unique_ptr<Component> component);

		template <typename T>
		T* GetComponent() const;

		GameObject() = default;
		~GameObject();

	private:
		std::vector<std::unique_ptr<Component>> components{};
	};

	template <typename T>
	T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
		for (const auto& component : components)
		{
			if (T* component_after_cast = dynamic_cast<T*>(component.get()))
			{
				return component_after_cast;
			}
		}
		throw std::runtime_error("Component not found");
	}

}