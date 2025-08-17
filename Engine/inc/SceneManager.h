#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "Singleton.h"
#include "Scene.h"

namespace engine
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		// Modifiable current scene, objects in it are updated and rendered and can die, move, etc.
		std::unique_ptr<Scene> current_scene;

		void Update(float delta_time);
		void LateUpdate();
		void Render();
		void FixedUpdate();

		void LoadScene(const std::string& scene_name);

		// Holds the instructions to load each scene
		std::map<std::string, std::function<void()>> scene_templates;
	private:
		SceneManager() = default;
		friend class Singleton<SceneManager>;
	};
}

