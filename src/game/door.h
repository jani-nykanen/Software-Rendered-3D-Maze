/// Door (header)
/// (c) 2017 Jani Nykänen

#ifndef __DOOR__
#define __DOOR__

#include "../engine/transform.h"
#include "player.h"

/// Door object
typedef struct
{
    VEC2 pos; /// Position
    bool opened; /// Is opened
    float angle; /// Door angle
    bool horizontal; /// Is horizontal
    bool locked; /// Is locked
}
DOOR;

/// Initialize doors (mostly init bitmaps)
void init_doors();

/// Create a door
/// < pos Position
/// < horizontal Is the door horizontal
/// < locked Is the door locked
/// > A door object
DOOR create_door(VEC2 pos, bool horizontal, bool locked);

/// Update the door and also take the player collision
/// < d Door to update
/// < pl Player object
/// < tm Time multiplier
void door_update(DOOR*d, PLAYER* pl, float tm);

/// Draw door
/// < Door to draw
/// < cam Camera
void door_draw(DOOR* d, CAMERA* cam);

#endif // __DOOR__