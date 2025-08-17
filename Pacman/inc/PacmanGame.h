#pragma once
#include "Game.h"
#include "GameMode.h"
#include "Command.h"

class PacmanGame : public engine::Game
{
public:
	PacmanGame(const std::string& dataPath);
	GameMode game_mode{ GameMode::Single }; // Default game mode is single player
private:
	// Creates the scenes like you would do in an editor in big engines. I have to do this in app because an editor is beyond the scope of the project. Some data will still be loaded through files, just not all components, parameters, references, settings, etc. like you'd see in a commercial engine.
	void BuildSceneTemplates();
};

class PacmanLoadCoopCommand final : public engine::Command
{
public:
	PacmanLoadCoopCommand(PacmanGame* game)
		: game(game)
	{}
	PacmanGame* game;
	void Execute()
	{
		game->game_mode = GameMode::Coop;
	}
};