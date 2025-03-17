#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

void engine::RenderComponent::Render() const
{
	const auto& pos = game_object->GetComponent<Transform>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*texture.get(), pos.x, pos.y);
}

void engine::RenderComponent::SetTexture(const std::string& file)
{
	texture = ResourceManager::GetInstance().LoadTexture(file);
}
