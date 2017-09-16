/// Stage (source)
/// (c) 2017 Jani Nykänen

#include "stage.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

/// Wall bitmap
static BITMAP* bmpWall;

/// Initialize stage
void init_stage()
{
    bmpWall = get_bitmap("wall");
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
    player_get_collision(pl,vec2(-4.0f,-4.0f),8.0f,false);
    player_get_collision(pl,vec2(4.0f,-4.0f),8.0f,false);
}

/// Draw stage
void stage_draw()
{
    set_floor_level(16);
    
    clear_frame(0b00010101);
    fill_rect(0,96,256,96,0b00101010);
    clear_depth();

    bind_texture(bmpWall);
    
    const float w = 1.0f;
    int i = 0;
    for(i=-4; i <= 3; i++)
    {
        draw_wall(vec2(i*w,4.0f),vec2( (i+1)*w,4.0f),1.5f);
        draw_wall(vec2(i*w,-4.0f),vec2( (i+1)*w,-4.0f),1.5f);
        draw_wall(vec2(-4.0f,i*w),vec2( -4.0f,(i+1)*w),1.5f);
        draw_wall(vec2(4.0f,i*w),vec2( 4.0f,(i+1)*w),1.5f);
    }
}
