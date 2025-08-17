#pragma once
#include <unordered_map>
#include "Singleton.h"
#include "Command.h"
#include <queue>

namespace engine
{
	enum class InputCode
	{
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_UP_ARROW,
		KEY_DOWN_ARROW,
		KEY_LEFT_ARROW,
		KEY_RIGHT_ARROW,
		P1_JOYSTICK_UP,
		P1_JOYSTICK_DOWN,
		P1_JOYSTICK_LEFT,
		P1_JOYSTICK_RIGHT,
		P2_JOYSTICK_UP,
		P2_JOYSTICK_DOWN,
		P2_JOYSTICK_LEFT,
		P2_JOYSTICK_RIGHT,
	};

    class InputManager final : public Singleton<InputManager>
    {
    public:
		~InputManager() { registered_commands.clear(); }

        bool ProcessInput();
		void RegisterCommand(InputCode input_code, Command* command);
		void UnregisterAllCommands() { registered_commands.clear(); }

    private:
        std::queue<InputCode> input_queue;
        std::unordered_map<InputCode, Command*> registered_commands;
    };

}