#pragma once
#include <string>

namespace engine
{
	/**
	 * @brief Contains the whole game application. Calls upon the game state to modify itself and render itself (ECS). Other than that it just holds some singletons.
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
	private:
		std::string name{"Unnamed game"};
	};
}