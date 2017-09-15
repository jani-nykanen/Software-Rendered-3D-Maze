/// Game scene (source)
/// (c) 2017 Jani Nykänen

#include "game.h"

#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/transform.h"
#include "../engine/controls.h"
#include "../engine/assets.h"

#include "camera.h"

/// Brick wall texture
static BITMAP* texWall;
/// Figure
static BITMAP* bmpFigure;
/// HUD
static BITMAP* bmpHud;

/// Game camera
static CAMERA cam;

/// Init game
static int game_init()
{
    texWall = get_bitmap("wall");
    bmpFigure = get_bitmap("figure");
    bmpHud = get_bitmap("hud");

    // Init camera
    cam.pos = vec3(0.0f,0.0f,4.0f);
    cam.angle = 0.0f;
    
    return 0;
}

/// Update game
/// tm Time multiplier
static void game_update(float tm)
{
    if(get_key_state((int)SDL_SCANCODE_LEFT) == DOWN)
    {
        cam.angle -= 0.025f * tm;
    }
    else if(get_key_state((int)SDL_SCANCODE_RIGHT) == DOWN)
    {
        cam.angle += 0.025f * tm;
    }

    if(get_key_state((int)SDL_SCANCODE_W) == DOWN)
    {
        cam.pos.z -= cos(cam.angle) * 0.05f * tm;
        cam.pos.x -= sin(cam.angle) * 0.05f * tm;
    }
    else if(get_key_state((int)SDL_SCANCODE_S) == DOWN)
    {
        cam.pos.z += cos(cam.angle) * 0.05f * tm;
        cam.pos.x += sin(cam.angle) * 0.05f * tm;
    }
    
    if(get_key_state((int)SDL_SCANCODE_A) == DOWN)
    {
        cam.pos.z -= cos(cam.angle - M_PI/2.0f) * 0.05f * tm;
        cam.pos.x -= sin(cam.angle - M_PI/2.0f) * 0.05f * tm;
    }
    else if(get_key_state((int)SDL_SCANCODE_D) == DOWN)
    {
        cam.pos.z += cos(cam.angle - M_PI/2.0f) * 0.05f * tm;
        cam.pos.x += sin(cam.angle - M_PI/2.0f) * 0.05f * tm;
    }

    // Limit camera
    if(cam.pos.z < -4.0f + 0.95f)
        cam.pos.z = -4.0f +0.95f;
    else if(cam.pos.z > +4.0f - 0.95f)
        cam.pos.z = 4.0f -0.95f;

    if(cam.pos.x < -4.0f + 0.95f)
        cam.pos.x = -4.0f +0.95f;
    else if(cam.pos.x > +4.0f - 0.95f)
        cam.pos.x = 4.0f -0.95f;
}

/// Draw game
static void game_draw()
{
    set_floor_level(16);

    clear_frame(0b00010101);
    fill_rect(0,96,256,96,0b00101010);
    clear_depth();

    tr_identity();
    use_camera(&cam);

    bind_texture(texWall);

    const float w = 1.0f;
    int i = 0;
    for(i=-4; i <= 3; i++)
    {
        draw_wall(vec2(i*w,4.0f),vec2( (i+1)*w,4.0f),1.5f);
        draw_wall(vec2(i*w,-4.0f),vec2( (i+1)*w,-4.0f),1.5f);
        draw_wall(vec2(-4.0f,i*w),vec2( -4.0f,(i+1)*w),1.5f);
        draw_wall(vec2(4.0f,i*w),vec2( 4.0f,(i+1)*w),1.5f);
    }

    VEC3 p1 = tr_use_transform(vec3(0.0f,1.0f,0.0f));
    VEC3 p2 = tr_use_transform(vec3(0.5f,1.0f,0.5f));

    if(p1.z > p2.z)
    {
        draw_sprite_3D(bmpFigure,vec3(0.0f,1.0f,0.0f),1.0f,1.0f);
        draw_sprite_3D(bmpFigure,vec3(1.5f,1.0f,0.5f),1.0f,1.0f);
    }
    else
    {
        draw_sprite_3D(bmpFigure,vec3(1.5f,1.0f,0.5f),1.0f,1.0f);
        draw_sprite_3D(bmpFigure,vec3(0.0f,1.0f,0.0f),1.0f,1.0f);
    }

    draw_bitmap(bmpHud,0,192);
}

/// Destroy game
static void game_destroy()
{

}

/// Get game scene
SCENE get_game_scene()
{
    // Set scene functions
    SCENE s = (SCENE){game_init,game_update,game_draw,game_destroy};

    // Set scene name
    set_scene_name(&s,"game");

    return s;
}