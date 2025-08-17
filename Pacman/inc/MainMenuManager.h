#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "GameMode.h"
#include "Command.h"
#include "SceneManager.h"

class MainMenuLoadCoopCommand final : public engine::Command
{
public:
	void Execute()
	{
		engine::SceneManager::GetInstance().LoadScene("Level1");
	}
};

class MainMenuManager final : public engine::Component
{
public:
	MainMenuManager() = default;
	~MainMenuManager() override = default;
	void Update(float delta_time) override { delta_time; }
	void Render() const override {};
	void LateUpdate() override {};
	void FixedUpdate() override {};
};