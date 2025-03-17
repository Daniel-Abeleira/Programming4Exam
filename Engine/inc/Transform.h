#pragma once
#include <glm.hpp>
#include "Component.h"

namespace engine
{
	class Transform final : public Component
	{
	public:
		Transform() = default;
		~Transform() = default;

		const glm::vec3& GetPosition() const { return position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos) { position = pos; }

		void Update(float delta_time) override { delta_time; /*To get rid of the unreferenced warning treated as error*/ };
		void Render() const override {};
		void LateUpdate() override {};
		void FixedUpdate() override {};
	private:
		glm::vec3 position{};
	};
}
