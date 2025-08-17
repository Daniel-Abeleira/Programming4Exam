#include "Pacman.h"

void Pacman::Update(float delta_time)
{
    float new_x = transform.GetPosition().x + direction_x * speed * delta_time;
    float new_y = transform.GetPosition().y + direction_y * speed * delta_time;
    float map_width = 464.0f;
    float map_height = 496.0f;

    // Loop Pacman horizontally
    if (new_x < 0.0f)
        new_x += map_width;
    else if (new_x >= map_width)
        new_x -= map_width;

    // Loop Pacman vertically
    if (new_y < 0.0f)
        new_y += map_height;
    else if (new_y >= map_height)
        new_y -= map_height;

    transform.SetPosition(
        new_x,
        new_y,
        transform.GetPosition().z
    );
}
