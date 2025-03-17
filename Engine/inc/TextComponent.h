#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

namespace engine
{
	class Font;
	class Texture2D;
	class TextComponent final : public Component
	{
	public:
		void Update(float delta_time) override;
		void Render() const override;
		void LateUpdate() override {};
		void FixedUpdate() override {};

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextComponent(const std::string& text, std::shared_ptr<Font> TTF_font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool needs_update;
		std::string text;
		Transform transform{};
		std::shared_ptr<Font> TTF_font;
		std::shared_ptr<Texture2D> text_texture;
	};

}