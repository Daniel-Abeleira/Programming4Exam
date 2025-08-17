#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"

namespace engine
{
	class Font;
	class Texture2D;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::filesystem::path& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::filesystem::path data_path;

		void UnloadUnusedResources();

		std::map<std::string, std::shared_ptr<Texture2D>> loaded_textures;
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> loaded_fonts;

	};
}
