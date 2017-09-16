/// Object controller (source)
/// (c) 2017 Jani Nykänen

#include "objcontrol.h"

#include "stage.h"
#include "object.h"

/// Player object
static PLAYER pl;
/// Non-player game objects
static OBJECT objs[32];

/// Init object controller
void init_object_control()
{
    pl = create_player(vec2(0.0f,2.0f));

    int i = 0;
    for(; i < 32; i++)
    {
        objs[i].exist = false;
    }
}

/// Update object controller
void update_obj_control(CAMERA* cam, float tm)
{
    player_update(&pl,tm);

    /// TEMPORARY COLLISIONS
    /// TODO: Move to stage.c
    stage_get_player_collision(&pl);

    player_set_camera(&pl,cam);
}
