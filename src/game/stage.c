/// Stage (source)
/// (c) 2017 Jani Nykänen

#include "stage.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

/// Wall bitmap
static BITMAP* bmpWall;
/// Background bitmap
static BITMAP* bmpBg;

/// Initialize stage
void init_stage()
{
    bmpWall = get_bitmap("wall");
    bmpBg = get_bitmap("bg");
}

/// Update stage
void stage_update(float tm)
{

}

/// Get player collision
void stage_get_player_collision(PLAYER* pl)
{
    player_get_collision(pl,vec2(-4.0f,4.0f),8.0f,true);
    player_get_collision(pl,vec2(-4.0f,-4.0f),8.0f,true);
    player_get_collision(pl,vec2(-4.0f,-4.0f),6.0f,false);
    player_get_collision(pl,vec2(4.0f,-4.0f),8.0f,false);
}

/// Draw stage
void stage_draw()
{
    set_floor_level(16);
    
    draw_bitmap(bmpBg,0,0);
    clear_depth();

    bind_texture(bmpWall);

    const float w = 1.0f;
    int i = 0;
    for(i=-4; i <= 3; i++)
    {
        set_wall_lines(true,true,i == -4,i == 3);

        draw_wall(vec2(i*w,4.0f),vec2( (i+1)*w,4.0f),1.5f);
        draw_wall(vec2(i*w,-4.0f),vec2( (i+1)*w,-4.0f),1.5f);
        draw_wall(vec2(-4.0f,i*w),vec2( -4.0f,(i+1)*w),1.5f);


        if(i >= -2)
        {
            set_wall_lines(true,true,i == -2,i == 3);
            draw_wall(vec2(4.0f,i*w),vec2( 4.0f,(i+1)*w),1.5f);
        }
    }
}
