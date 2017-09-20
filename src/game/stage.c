/// Stage (source)
/// (c) 2017 Jani Nykänen

#include "stage.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

/// Wall bitmap
static BITMAP* bmpWall;
/// Background bitmap
static BITMAP* bmpBg;

/// Current map
static TILEMAP* map;

/// Draw wall by tile id
/// < x X coordinate in map coordinates
/// < y Y coord
/// < tid Tileid
static void draw_tilemap_wall(int x, int y, Uint8 tid)
{
    set_wall_lines(true,true,false,false);

    if(tid == 1 || tid == 5 || tid == 7 || tid == 10 || tid == 11 || tid == 12 || tid == 14 || tid == 15)
    {
        draw_wall(vec2(x*2.0f,y*2.0f),vec2( x*2.0f + 1.0f,y*2.0f),1.5f);
        draw_wall(vec2(x*2.0f +1.0f,y*2.0f),vec2( (x+1)*2.0f,y*2.0f),1.5f);
    }

    if(tid == 3 || tid == 5 || tid == 8 || tid == 9 || tid == 12 || tid == 13 || tid == 14 || tid == 15)
    {
        draw_wall(vec2(x*2.0f,y*2.0f +2.0f),vec2( x*2.0f + 1.0f,y*2.0f +2.0f),1.5f);
        draw_wall(vec2(x*2.0f +1.0f,y*2.0f +2.0f),vec2( (x+1)*2.0f,y*2.0f +2.0f),1.5f);
    }

    if(tid == 2 || tid == 6 || tid == 7 || tid == 8 || tid == 11 || tid == 12 || tid == 13 || tid == 15)
    {
        draw_wall(vec2(x*2.0f + 2.0f,y*2.0f),vec2( x*2.0f + 2.0f,y*2.0f +1.0f),1.5f);
        draw_wall(vec2(x*2.0f + 2.0f,y*2.0f +1.0f),vec2( x*2.0f + 2.0f,y*2.0f +2.0f),1.5f);
    }

    if(tid == 4 || tid == 6 || tid == 9 || tid == 10 || tid == 11 || tid == 13 || tid == 14 || tid == 15)
    {
        draw_wall(vec2(x*2.0f,y*2.0f),vec2( x*2.0f,y*2.0f +1.0f),1.5f);
        draw_wall(vec2(x*2.0f,y*2.0f +1.0f),vec2( x*2.0f,y*2.0f +2.0f),1.5f);
    }
}

/// Draw tilemap to "3D" space
/// < cam Camera
static void draw_tilemap(CAMERA* cam)
{
    VEC3 cpos = cam->pos;

    int cx = (int)floor(-cpos.x / 2.0f);
    int cy = (int)floor(-cpos.z / 2.0f);

    int sx = cx - 5;
    int sy = cy - 5;

    if(sx < 0) sx = 0;
    if(sy < 0) sy = 0;

    int ex = cx + 5;
    int ey = cy + 5;

    if(ex >= map->w) ex = map->w-1;
    if(ey >= map->h) ey = map->h-1;

    int x = 0;
    int y = 0;
    for(y = sy; y <= ey; y++)
    {
        for(x = sx; x <= ex; x++)
        {
            draw_tilemap_wall(x,y, map->layers[0] [y*map->w + x] );
        }
    }
}

/// Initialize stage
void init_stage()
{
    bmpWall = get_bitmap("wall");
    bmpBg = get_bitmap("bg");

    map = get_tilemap("test");
}

/// Update stage
void stage_update(float tm)
{

}

/// Get player collision
void stage_get_player_collision(PLAYER* pl)
{
    int cx = (int)floor(-pl->pos.x / 2.0f);
    int cy = (int)floor(-pl->pos.y / 2.0f);

    int sx = cx - 3;
    int sy = cy - 3;

    if(sx < 0) sx = 0;
    if(sy < 0) sy = 0;

    int ex = cx + 3;
    int ey = cy + 3;

    if(ex >= map->w) ex = map->w-1;
    if(ey >= map->h) ey = map->h-1;

    int x = 0;
    int y = 0;
    Uint8 tid;
    for(y = sy; y <= ey; y++)
    {
        for(x = sx; x <= ex; x++)
        {
            tid = map->layers[0] [y*map->w + x] ;

            if(tid == 1 || tid == 5 || tid == 7 || tid == 10 || tid == 11 || tid == 12 || tid == 14 || tid == 15)
            {
                player_get_collision(pl,vec2(-(x+1)*2.0f,-y*2.0f),2.0f,true);
            }
        
            if(tid == 3 || tid == 5 || tid == 8 || tid == 9 || tid == 12 || tid == 13 || tid == 14 || tid == 15)
            {
                player_get_collision(pl,vec2(-(x+1)*2.0f,-(y+1)*2.0f),2.0f,true);
            }
        
            if(tid == 2 || tid == 6 || tid == 7 || tid == 8 || tid == 11 || tid == 12 || tid == 13 || tid == 15)
            {
                player_get_collision(pl,vec2(-(x+1)*2.0f,-(y+1)*2.0f),2.0f,false);
            }
        
            if(tid == 4 || tid == 6 || tid == 9 || tid == 10 || tid == 11 || tid == 13 || tid == 14 || tid == 15)
            {
                player_get_collision(pl,vec2(-(x)*2.0f,-(y+1)*2.0f),2.0f,false);
            }
        }
    }
}

/// Draw stage
void stage_draw(CAMERA* cam)
{
    set_floor_level(16);
    
    draw_bitmap(bmpBg,0,0);
    clear_depth();

    bind_texture(bmpWall);
    set_tex_area(0.0f,0.0f,1.0f,1.0f);

    set_wall_lines(true,true,false,false);

    draw_tilemap(cam);    
}
