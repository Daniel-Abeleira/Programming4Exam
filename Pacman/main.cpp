#include <SDL.h>
#include <memory>
#include <iostream>
#include "SceneManager.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <filesystem>
namespace fs = std::filesystem;

#include "PacmanGame.h"

int main(int, char* [])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif

	std::unique_ptr<PacmanGame> game = std::make_unique<PacmanGame>(data_location.string());
	try
	{
		engine::SceneManager::GetInstance().LoadScene("MainMenu"); //Sets the initial scene. In the final version it will be "MainMenu" or similar.
		game->Run(); // Full game loop all the way through to exit_called
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}