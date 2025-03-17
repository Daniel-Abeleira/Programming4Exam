#include "SceneBuilder.h"
#include <iostream>
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

void SceneBuilder::BuildScenes(engine::Game& game)
{
	//std::cout << "Building scenes\n";
	//auto& scene_manager = engine::SceneManager::GetInstance();

	//scene_manager.scenes["Singleplayer"] = std::make_shared<engine::Scene>("Singleplayer");

	//auto bg_image = std::make_shared<engine::GameObject>();
	//bg_image->AddComponent(std::make_unique<engine::Transform>());
	//bg_image->AddComponent(std::make_unique<engine::RenderComponent>());
	//bg_image->GetComponent<engine::RenderComponent>()->SetTexture("background.tga");
	//scene_manager.scenes["Singleplayer"]->Add(bg_image);

	//auto go_fps_counter = std::make_shared<engine::GameObject>();
	//go_fps_counter = std::make_shared<engine::GameObject>();
	//go_fps_counter->AddComponent(std::make_unique<engine::TextComponent>("Hello World", engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)));
	//scene_manager.scenes["Singleplayer"]->Add(go_fps_counter);
}
