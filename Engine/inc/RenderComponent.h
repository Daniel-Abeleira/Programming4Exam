#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <optional>
#include "Component.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace engine
{
	struct Animation
	{
	public:
		int initial_frame;
		int final_frame;
		float seconds_per_frame;
		std::string file_name;
	};

	class RenderComponent :
		public Component
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		void Update(float delta_time) override;
		void Render() const override;
		void LateUpdate() override {};
		void FixedUpdate() override {};

		void SetTexture(const std::string& file);
        
		void AddAnimation(const std::string& handle_name, const std::string& file_name, int initial_frame, int final_frame, float seconds_per_frame);
		void SetCurrentAnimation(const std::string& name);

	private:
		std::shared_ptr<Texture2D> texture;
		// Animation
		std::unordered_map<std::string, Animation> animations;
		std::optional<std::string> current_animation{std::nullopt};
		int current_frame{ 0 };
		float seconds_to_next_frame{ 0.0f };
	};

}