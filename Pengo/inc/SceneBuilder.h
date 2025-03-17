#pragma once
#include "Game.h"

/**
 * @brief Effectively just a functor to build all the scenes in the app instead of doing it in main.cpp. In a more long-term project this would go inside the engine and load not only the scenes but also settings and even resources from scene files and other assets. But that would require the engine having a complete scene editor.
 */
class SceneBuilder
{
public:
	SceneBuilder() = default;
	~SceneBuilder() = default;
	void BuildScenes(engine::Game& game);
};