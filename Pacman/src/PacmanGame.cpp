#include "PacmanGame.h"

#include <memory>
#include <iostream>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "MainMenuManager.h"

#include "Pacman.h"

PacmanGame::PacmanGame(const std::string& dataPath) : Game("Pacman", dataPath)
{
	BuildSceneTemplates();
	engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_F2, new PacmanLoadCoopCommand(this));
}

void PacmanGame::BuildSceneTemplates()
{
	auto test_scene = []()
		{
			auto& scene = engine::SceneManager::GetInstance().current_scene;

			//===MS Pacman===
			auto ms_pacman = std::make_shared<engine::GameObject>();
			ms_pacman->AddComponent(std::make_unique<engine::Transform>());
			ms_pacman->GetComponent<engine::Transform>()->SetPosition(50.0f, 50.0f, 0.0f);
			ms_pacman->AddComponent(std::make_unique<engine::RenderComponent>());
			ms_pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_r", "ms_pacman_move", 0, 2, 0.1f);
			ms_pacman->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_r");
			ms_pacman->AddComponent(std::make_unique<Pacman>(*(ms_pacman->GetComponent<engine::Transform>())));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_UP_ARROW, new PacmanMoveUpCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_DOWN_ARROW, new PacmanMoveDownCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_LEFT_ARROW, new PacmanMoveLeftCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_RIGHT_ARROW, new PacmanMoveRightCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_UP, new PacmanMoveUpCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_DOWN, new PacmanMoveDownCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_LEFT, new PacmanMoveLeftCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_RIGHT, new PacmanMoveRightCommand(ms_pacman->GetComponent<Pacman>()));
			scene->Add(ms_pacman);
			//===MS Pacman===

			auto go_fps_counter = std::make_shared<engine::GameObject>();
			go_fps_counter = std::make_shared<engine::GameObject>();
			go_fps_counter->AddComponent(std::make_unique<engine::TextComponent>("Hello World", engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14)));
			scene->Add(go_fps_counter);
		};
	engine::SceneManager::GetInstance().scene_templates.insert_or_assign("TestScene", test_scene);

	auto main_menu = []()
		{
			auto& scene = engine::SceneManager::GetInstance().current_scene;

			auto info_title = std::make_shared<engine::GameObject>();
			info_title->AddComponent(std::make_unique<engine::TextComponent>("MS. PACMAN", engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24)));
			info_title->GetComponent<engine::TextComponent>()->SetPosition(50.0f, 20.0f);
			scene->Add(info_title);

			auto info_author = std::make_shared<engine::GameObject>();
			info_author->AddComponent(std::make_unique<engine::TextComponent>("by Daniel Abeleira", engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14)));
			info_author->GetComponent<engine::TextComponent>()->SetPosition(50.0f, 70.0f);
			scene->Add(info_author);

			auto mode_selector = std::make_shared<engine::GameObject>();
			mode_selector->AddComponent(std::make_unique<MainMenuManager>());
			mode_selector->AddComponent(std::make_unique<engine::TextComponent>("[F1] Single [F2] Coop [F3] Versus", engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14)));
			mode_selector->GetComponent<engine::TextComponent>()->SetPosition(50.0f, 90.0f);
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_F2, new MainMenuLoadCoopCommand());
			scene->Add(mode_selector);
		};
	engine::SceneManager::GetInstance().scene_templates.insert_or_assign("MainMenu", main_menu);

	auto level_1 = []()
		{
			auto& scene = engine::SceneManager::GetInstance().current_scene;

			auto bg = std::make_shared<engine::GameObject>();
			bg->AddComponent(std::make_unique<engine::Transform>());
			bg->AddComponent(std::make_unique<engine::RenderComponent>());
			bg->GetComponent<engine::RenderComponent>()->SetTexture("level1.tga");
			scene->Add(bg);

			//===Ms Pacman===
			auto ms_pacman = std::make_shared<engine::GameObject>();
			ms_pacman->AddComponent(std::make_unique<engine::Transform>());
			ms_pacman->GetComponent<engine::Transform>()->SetPosition(50.0f, 50.0f, 0.0f);
			ms_pacman->AddComponent(std::make_unique<engine::RenderComponent>());
			ms_pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_r", "ms_pacman_move", 0, 2, 0.1f);
			ms_pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_l", "ms_pacman_move", 3, 5, 0.1f);
			ms_pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_u", "ms_pacman_move", 6, 8, 0.1f);
			ms_pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_d", "ms_pacman_move", 9, 11, 0.1f);
			ms_pacman->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_r");
			ms_pacman->AddComponent(std::make_unique<Pacman>(*(ms_pacman->GetComponent<engine::Transform>())));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_UP_ARROW, new PacmanMoveUpCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_DOWN_ARROW, new PacmanMoveDownCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_LEFT_ARROW, new PacmanMoveLeftCommand(ms_pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::KEY_RIGHT_ARROW, new PacmanMoveRightCommand(ms_pacman->GetComponent<Pacman>()));
			scene->Add(ms_pacman);
			//===Ms Pacman===
			
			//===Mr Pacman===
			auto pacman = std::make_shared<engine::GameObject>();
			pacman->AddComponent(std::make_unique<engine::Transform>());
			pacman->GetComponent<engine::Transform>()->SetPosition(150.0f, 50.0f, 0.0f);
			pacman->AddComponent(std::make_unique<engine::RenderComponent>());
			pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_r", "pacman_move", 0, 1, 0.1f);
			pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_l", "pacman_move", 2, 3, 0.1f);
			pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_u", "pacman_move", 4, 5, 0.1f);
			pacman->GetComponent<engine::RenderComponent>()->AddAnimation("move_d", "pacman_move", 6, 7, 0.1f);
			pacman->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_r");
			pacman->AddComponent(std::make_unique<Pacman>(*(pacman->GetComponent<engine::Transform>())));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_UP, new PacmanMoveUpCommand(pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_DOWN, new PacmanMoveDownCommand(pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_LEFT, new PacmanMoveLeftCommand(pacman->GetComponent<Pacman>()));
			engine::InputManager::GetInstance().RegisterCommand(engine::InputCode::P1_JOYSTICK_RIGHT, new PacmanMoveRightCommand(pacman->GetComponent<Pacman>()));
			scene->Add(pacman);
			//===Mr Pacman===
		};
	engine::SceneManager::GetInstance().scene_templates.insert_or_assign("Level1", level_1);

	std::cout << "Scene templates built\n";
}