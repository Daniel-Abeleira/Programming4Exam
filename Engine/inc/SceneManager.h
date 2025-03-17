#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
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
	private:
		SceneManager() = default;
		friend class Singleton<SceneManager>;
	};
}

