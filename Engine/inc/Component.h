#pragma once

namespace engine
{
	class GameObject;

	class Component
	{
	public:
		Component() {}
		virtual ~Component() = default;

		virtual void Update(float delta_time) = 0;
		virtual void Render() const = 0;
		virtual void LateUpdate() = 0;
		virtual void FixedUpdate() = 0;

		GameObject* game_object{};
	private:
	};
}