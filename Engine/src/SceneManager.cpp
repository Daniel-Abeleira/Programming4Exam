#include "SceneManager.h"

void engine::SceneManager::Update(float delta_time)
{
    if (current_scene)
    {
        current_scene->Update(delta_time);
    }
}

void engine::SceneManager::LateUpdate()
{}

void engine::SceneManager::Render()
{
    if (current_scene)
    {
        current_scene->Render();
    }
}

void engine::SceneManager::FixedUpdate()
{}