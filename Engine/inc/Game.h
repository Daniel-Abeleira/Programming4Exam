#pragma once

namespace engine
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;
		void Run();
	};
}