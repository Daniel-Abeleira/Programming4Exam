#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

namespace fs = std::filesystem;

void engine::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	data_path = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<engine::Texture2D> engine::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = data_path / file;
	const auto filename = fs::path(fullPath).filename().string();
	if (loaded_textures.find(filename) == loaded_textures.end())
		loaded_textures.insert(std::pair(filename, std::make_shared<Texture2D>(fullPath.string())));
	return loaded_textures.at(filename);
}

std::shared_ptr<engine::Font> engine::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto fullPath = data_path / file;
	const auto filename = fs::path(fullPath).filename().string();
	const auto key = std::pair<std::string, uint8_t>(filename, size);
	if (loaded_fonts.find(key) == loaded_fonts.end())
		loaded_fonts.insert(std::pair(key, std::make_shared<Font>(fullPath.string(), size)));
	return loaded_fonts.at(key);
}

void engine::ResourceManager::UnloadUnusedResources()
{
	for (auto it = loaded_textures.begin(); it != loaded_textures.end();)
	{
		if (it->second.use_count() == 1)
			it = loaded_textures.erase(it);
		else
			++it;
	}

	for (auto it = loaded_fonts.begin(); it != loaded_fonts.end();)
	{
		if (it->second.use_count() == 1)
			it = loaded_fonts.erase(it);
		else
			++it;
	}
}
