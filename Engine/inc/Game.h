#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

namespace engine
{
	/**
  * @brief Contains the whole game application. Calls upon the game state to modify itself and render itself (ECS). Other than that it just holds some singletons and data.
  */
	class Game
	{
	public:
		Game(const std::string& name, const std::string& dataPath);
		virtual ~Game();
		virtual void Run();

		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator= (const Game&) = delete;
		Game& operator= (const Game&&) = delete;

	protected:
		std::string name{"Unnamed game"};
	};
}