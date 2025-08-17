#pragma once 
#include "Component.h"

#include <iostream>
#include "Transform.h"
#include "Command.h"
#include "RenderComponent.h"
#include "GameObject.h"

class Pacman final : public engine::Component
{
public:
	Pacman(engine::Transform& transform)
		: transform(transform)
	{}
	void Update(float delta_time) override;
	void Render() const override {}
	void LateUpdate() override {}
	void FixedUpdate() override {}

	void MoveUp() { direction_x = 0.0f; direction_y = -1.0f; game_object->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_u"); }
	void MoveDown(){ direction_x = 0.0f; direction_y = 1.0f; game_object->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_d"); }
	void MoveLeft() { direction_x = -1.0f; direction_y = 0.0f; game_object->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_l"); }
	void MoveRight() { direction_x = 1.0f; direction_y = 0.0f; game_object->GetComponent<engine::RenderComponent>()->SetCurrentAnimation("move_r"); }
private:
	// References
	engine::Transform& transform;

	float speed{ 100.0f };
	float direction_x{ 0.0f };
	float direction_y{ 0.0f };
};

class PacmanMoveUpCommand final : public engine::Command
{
public:
	PacmanMoveUpCommand(Pacman* pacman)
		: pacman(pacman)
	{}
	Pacman* pacman;
	void Execute() override
	{
		//std::cout << "PacmanMoveUpCommand executed\n";
		pacman->MoveUp();
	}
};
class PacmanMoveDownCommand final : public engine::Command
{
public:
	PacmanMoveDownCommand(Pacman* pacman)
		: pacman(pacman)
	{}
	Pacman* pacman;
	void Execute() override
	{
		//std::cout << "PacmanMoveDownCommand executed\n";
		pacman->MoveDown();
	}
};
class PacmanMoveLeftCommand final : public engine::Command
{
public:
	PacmanMoveLeftCommand(Pacman* pacman)
		: pacman(pacman)
	{}
	Pacman* pacman;
	void Execute() override
	{
		//std::cout << "PacmanMoveLeftCommand executed\n";
		pacman->MoveLeft();
	}
};
class PacmanMoveRightCommand final : public engine::Command
{
public:
	PacmanMoveRightCommand(Pacman* pacman)
		: pacman(pacman)
	{}
	Pacman* pacman;
	void Execute() override
	{
		//std::cout << "PacmanMoveRightCommand executed\n";
		pacman->MoveRight();
	}
};