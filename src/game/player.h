/// Player object (header)
/// (c) 2017 Jani Nykänen

#ifndef __PLAYER__
#define __PLAYER__

#include "../engine/transform.h"
#include "camera.h"

#include "stdbool.h"

/// Player object
typedef struct
{
    VEC2 pos; /// Position
    VEC2 speed; /// Speed
    VEC2 target; /// Target speed
    float totalSpeed; /// Speed vector Euclidean norm
    float angle; /// Angle, obviously
    float speedMul; /// Speed multiplier
    float maxSpeed; /// Maximum speed
    float turnSpeed; /// Turning speed
    float radius; /// Hitbox radius
    bool crouch; /// Is crouching
    bool running; /// Is running
    float bumpTimer; /// Bump is a good term for those running ups and downs
}
PLAYER;

/// Create a player object (mostly set default values)
/// < pos Starting position
/// > A player object
PLAYER create_player(VEC2 pos);

/// Update player
/// < pl Player to update
/// < tm Time multiplier
void player_update(PLAYER* pl, float tm);

/// Set camera to follow player
/// < pl Player
/// < cam Camera
/// < tm Time mul.
void player_set_camera(PLAYER* pl, CAMERA* cam, float tm);

/// Get (wall) collision
/// < pl Player to collide
/// < p Collider location
/// < w Collider width
/// < horizontal Is wall horizontal (delta-z = 0)
void player_get_collision(PLAYER*pl, VEC2 p, float w, bool horizontal);

#endif // __PLAYER__