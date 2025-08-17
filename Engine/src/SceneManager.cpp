#include "SceneManager.h"

#include <stdexcept>

void engine::SceneManager::Update(float delta_time)
{
    if (current_scene)
    {
        current_scene->Update(delta_time);
    }
}

void engine::SceneManager::LateUpdate()
{

}

void engine::SceneManager::Render()
{
    if (current_scene)
    {
        current_scene->Render();
    }
}

void engine::SceneManager::FixedUpdate()
{

}

void engine::SceneManager::LoadScene(const std::string & scene_name)
{
	current_scene.reset(new Scene(scene_name));
    if (scene_templates.find(scene_name) == scene_templates.end())
    {
		throw std::runtime_error("Tried to load scene '" + scene_name + "' but a template for it wasn't found!");
    }
	scene_templates[scene_name]();
}
