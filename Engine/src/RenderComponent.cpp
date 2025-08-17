#include "RenderComponent.h"

#include <iostream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

void engine::RenderComponent::Update(float delta_time)
{

	if (current_animation.has_value())
	{
		if (animations.find(*current_animation) == animations.end())
		{
			throw std::runtime_error("Animation '" + *current_animation + "' not found in RenderComponent!");
		}
		// Update animation frame
		seconds_to_next_frame -= delta_time;
		if (seconds_to_next_frame <= 0.0f)
		{
			const auto& anim = animations.at(*current_animation);
			current_frame++;
			if (current_frame > anim.final_frame)
			{
				current_frame = anim.initial_frame; // Loop back to the start
			}
			seconds_to_next_frame = anim.seconds_per_frame;
		}
	}
}

void engine::RenderComponent::Render() const
{
	if (!current_animation.has_value())
	{
		const auto& pos = game_object->GetComponent<Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*texture.get(), pos.x, pos.y);
	}
	else
	{
		// Animation rendering
		const auto& anim = animations.at(*current_animation);
		// Calculate current frame file name, e.g. "walk3.tga"
		std::string frame_file = anim.file_name + std::to_string(current_frame) + ".tga";
		// Load texture for current frame (ideally cache this in production)
		auto frame_texture = ResourceManager::GetInstance().LoadTexture(frame_file);
		const auto& pos = game_object->GetComponent<Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*frame_texture.get(), pos.x, pos.y);
	}
}

void engine::RenderComponent::SetTexture(const std::string& handle_name)
{
	texture = ResourceManager::GetInstance().LoadTexture(handle_name);
}

void engine::RenderComponent::AddAnimation(const std::string& handle_name, const std::string& file_name, int initial_frame, int final_frame, float seconds_per_frame)
{
	animations.insert_or_assign(handle_name, Animation{ initial_frame, final_frame, seconds_per_frame, file_name });
}

void engine::RenderComponent::SetCurrentAnimation(const std::string& name)
{
	for (const auto& [anim_name, anim] : animations)
	{
		if (anim_name == name)
		{
			current_animation = name;
			current_frame = anim.initial_frame;
			seconds_to_next_frame = anim.seconds_per_frame;
			return;
		}
	}
}
