#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <queue> // Include the necessary header for std::queue

bool engine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				// F-keys
			case SDLK_F1: input_queue.push(InputCode::KEY_F1); break;
			case SDLK_F2: input_queue.push(InputCode::KEY_F2); break;
			case SDLK_F3: input_queue.push(InputCode::KEY_F3); break;
			case SDLK_F4: input_queue.push(InputCode::KEY_F4); break;
				// Arrow keys
			case SDLK_UP: input_queue.push(InputCode::KEY_UP_ARROW); break;
			case SDLK_DOWN: input_queue.push(InputCode::KEY_DOWN_ARROW); break;
			case SDLK_LEFT: input_queue.push(InputCode::KEY_LEFT_ARROW); break;
			case SDLK_RIGHT: input_queue.push(InputCode::KEY_RIGHT_ARROW); break;
				// Letter keys
			case SDLK_a: input_queue.push(InputCode::KEY_A); break;
			case SDLK_b: input_queue.push(InputCode::KEY_B); break;
			case SDLK_c: input_queue.push(InputCode::KEY_C); break;
			case SDLK_d: input_queue.push(InputCode::KEY_D); break;
			case SDLK_e: input_queue.push(InputCode::KEY_E); break;
			case SDLK_f: input_queue.push(InputCode::KEY_F); break;
			case SDLK_g: input_queue.push(InputCode::KEY_G); break;
			case SDLK_h: input_queue.push(InputCode::KEY_H); break;
			case SDLK_i: input_queue.push(InputCode::KEY_I); break;
			case SDLK_j: input_queue.push(InputCode::KEY_J); break;
			case SDLK_k: input_queue.push(InputCode::KEY_K); break;
			case SDLK_l: input_queue.push(InputCode::KEY_L); break;
			case SDLK_m: input_queue.push(InputCode::KEY_M); break;
			case SDLK_n: input_queue.push(InputCode::KEY_N); break;
			case SDLK_o: input_queue.push(InputCode::KEY_O); break;
			case SDLK_p: input_queue.push(InputCode::KEY_P); break;
			case SDLK_q: input_queue.push(InputCode::KEY_Q); break;
			case SDLK_r: input_queue.push(InputCode::KEY_R); break;
			case SDLK_s: input_queue.push(InputCode::KEY_S); break;
			case SDLK_t: input_queue.push(InputCode::KEY_T); break;
			case SDLK_u: input_queue.push(InputCode::KEY_U); break;
			case SDLK_v: input_queue.push(InputCode::KEY_V); break;
			case SDLK_w: input_queue.push(InputCode::KEY_W); break;
			case SDLK_x: input_queue.push(InputCode::KEY_X); break;
			case SDLK_y: input_queue.push(InputCode::KEY_Y); break;
			case SDLK_z: input_queue.push(InputCode::KEY_Z); break;
			default: break;
			}
			break;

		case SDL_JOYAXISMOTION:
			if (e.jaxis.axis == 0) // Horizontal axis
			{
				if (e.jaxis.value < -3200) { input_queue.push(InputCode::P1_JOYSTICK_LEFT); }
				else if (e.jaxis.value > 3200) { input_queue.push(InputCode::P1_JOYSTICK_RIGHT); }
			}
			else if (e.jaxis.axis == 1) // Vertical axis
			{
				if (e.jaxis.value < -3200) { input_queue.push(InputCode::P1_JOYSTICK_UP); }
				else if (e.jaxis.value > 3200) { input_queue.push(InputCode::P1_JOYSTICK_DOWN); }
			}
			break;

		default:
			break;
		}
	}

	while (!input_queue.empty())
	{
		auto input = input_queue.front();
		input_queue.pop();

		auto it = registered_commands.find(input);
		if (it != registered_commands.end())
		{
			it->second->Execute();
		}
	}
	return true;
}


void engine::InputManager::RegisterCommand(InputCode input_code, Command* command)
{
	registered_commands.insert_or_assign(input_code, command);
}
