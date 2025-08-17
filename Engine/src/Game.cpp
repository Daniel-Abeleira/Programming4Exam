#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};
void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
		printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

engine::Game::Game(const std::string& name, const std::string& dataPath)
	: name(name)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	printf("The names of the joysticks are:\n");
    // Declare the variable 'i' as a constant value before the loop to fix the error E0028  
    const int joystickCount = SDL_NumJoysticks();  
    for (int i = 0; i < joystickCount; i++)  
    {  
		std::cout << SDL_JoystickNameForIndex(i) << std::endl;
    }
	if (joystickCount > 0)
	{
		SDL_Joystick* joystick;

		SDL_JoystickEventState(SDL_ENABLE);
		joystick = SDL_JoystickOpen(0);
	}
	if (joystickCount > 1)
	{
		SDL_Joystick* joystick2;
		SDL_JoystickEventState(SDL_ENABLE);
		joystick2 = SDL_JoystickOpen(1);
	}

	g_window = SDL_CreateWindow(
		name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		464,
		496,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

	std::cout << "Game [" << name << "] was constructed\n";
}

engine::Game::~Game()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
	std::cout << "Game [" << name << "] was destroyed\n";
}

void engine::Game::Run()
{
	std::cout << "Game [" << name << "] started running\n";
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool should_exit{ false };
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag{};
	constexpr float FIXED_TIME_STEP{ 1.f / 60.f };
	constexpr float DESIRED_FRAME_TIME{ 1.f / 60.f };
	while (!should_exit)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		while (lag >= FIXED_TIME_STEP)
		{
			// Fixed Update
			sceneManager.FixedUpdate();
			lag -= FIXED_TIME_STEP;
		}
		should_exit = !input.ProcessInput();
		sceneManager.Update(deltaTime);
		sceneManager.LateUpdate();
		renderer.Render();
		const auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::duration<float, std::milli>(DESIRED_FRAME_TIME));
		const auto sleepTime = currentTime + frameDuration - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}
