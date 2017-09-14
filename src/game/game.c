/// Game scene (source)
/// (c) 2017 Jani Nykänen

#include "game.h"

#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/transform.h"
#include "../engine/controls.h"

#include "camera.h"

/// Brick wall texture
static BITMAP* texWall;
/// Figure
static BITMAP* bmpFigure;

/// Game camera
static CAMERA cam;

/// Init game
static int game_init()
{
    texWall = load_bitmap("assets/textures/wall.png");
    if(texWall == NULL)
    {
        return 1;
    }

    bmpFigure = load_bitmap("assets/textures/figure.png");
    if(bmpFigure == NULL)
    {
        return 1;
    }

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
}

/// Draw game
static void game_draw()
{
    clear_frame(0b00101010);
    clear_depth();

    tr_identity();
    use_camera(&cam);

    bind_texture(texWall);

    draw_wall(vec2(-1.0f,2.0f),vec2(0.0f,2.0f),2.0f);
    draw_wall(vec2(0.0f,2.0f),vec2(1.0f,2.0f),2.0f);

    draw_wall(vec2(-1.0f,-2.0f),vec2(0.0f,-2.0f),2.0f);
    draw_wall(vec2(0.0f,-2.0f),vec2(1.0f,-2.0f),2.0f);

    VEC3 p1 = tr_use_transform(vec3(0.0f,1.0f,0.0f));
    VEC3 p2 = tr_use_transform(vec3(0.5f,1.0f,0.5f));

    if(p1.z > p2.z)
    {
        draw_sprite_3D(bmpFigure,vec3(0.0f,1.0f,0.0f),1.5f,1.5f);
        draw_sprite_3D(bmpFigure,vec3(0.5f,1.0f,0.5f),1.5f,1.5f);
    }
    else
    {
        draw_sprite_3D(bmpFigure,vec3(0.5f,1.0f,0.5f),1.5f,1.5f);
        draw_sprite_3D(bmpFigure,vec3(0.0f,1.0f,0.0f),1.5f,1.5f);
    }
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