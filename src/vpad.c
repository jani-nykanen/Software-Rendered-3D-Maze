/// Virtual game pad (source)
/// (c) 2017 Jani Nykänen

#include "vpad.h"

/// The good ol' gamepad stick
static VEC2 stick;

/// Initialize virtual gamepad
void vpad_init()
{
    stick.x = 0.0f;
    stick.y = 0.0f;
}

/// Get stick axis
VEC2 vpad_get_stick()
{
    return stick;
}

/// Update vpad
void vpad_update()
{
    stick.x = 0.0f;
    stick.y = 0.0f;

    if(get_key_state((int)SDL_SCANCODE_LEFT) == DOWN)
    {
        stick.x = -1.0f;
    }
    else if(get_key_state((int)SDL_SCANCODE_RIGHT) == DOWN)
    {
        stick.x = 1.0f;
    }

    if(get_key_state((int)SDL_SCANCODE_UP) == DOWN)
    {
        stick.y = -1.0f;
    }
    else if(get_key_state((int)SDL_SCANCODE_DOWN) == DOWN)
    {
        stick.y = 1.0f;
    }
}