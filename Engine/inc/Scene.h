#pragma once
#include <vector>
#include <string>
#include <memory>

namespace engine
{
	class GameObject;

	class Scene final
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update(float delta_time);
		void Render() const;
		void FixedUpdate();
		void LateUpdate();

		const std::string& GetName() const { return name; }

		~Scene() = default;
		explicit Scene(const std::string& name);

	private:

		std::string name;
		std::vector<std::shared_ptr<GameObject>> objects{};

	};
}
