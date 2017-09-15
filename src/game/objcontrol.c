/// Object controller (source)
/// (c) 2017 Jani Nykänen

#include "objcontrol.h"

/// Player object
static PLAYER pl;

/// Init object controller
void init_object_control()
{
    pl = create_player(vec2(0.0f,2.0f));
}

/// Update object controller
void update_obj_control(CAMERA* cam, float tm)
{
    player_update(&pl,tm);

    /// TEMPORARY COLLISIONS
    /// TODO: Move to stage.c
    player_get_collision(&pl,vec2(-4.0f,4.0f),8.0f,true);
    player_get_collision(&pl,vec2(-4.0f,-4.0f),8.0f,true);
    player_get_collision(&pl,vec2(-4.0f,-4.0f),8.0f,false);
    player_get_collision(&pl,vec2(4.0f,-4.0f),8.0f,false);

    player_set_camera(&pl,cam);
}
