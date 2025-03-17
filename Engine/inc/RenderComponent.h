#pragma once
#include <memory>
#include "Component.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace engine
{
	class RenderComponent :
		public Component
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		void Update(float delta_time) override { delta_time; /*To get rid of the unreferenced warning treated as error*/ };
		void Render() const override;
		void LateUpdate() override {};
		void FixedUpdate() override {};

		void SetTexture(const std::string& file);
	private:
		std::shared_ptr<Texture2D> texture;
	};

}