/// Game scene (source)
/// (c) 2017 Jani Nykänen

#include "game.h"

#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/transform.h"
#include "../engine/controls.h"
#include "../engine/assets.h"

#include "camera.h"
#include "objcontrol.h"
#include "stage.h"
#include "hud.h"

#include "../vpad.h"

/// Figure
static BITMAP* bmpFigure;

/// Game camera
static CAMERA cam;

/// Init game
static int game_init()
{
    bmpFigure = get_bitmap("figure");

    // Init camera
    cam.pos = vec3(0.0f,0.0f,4.0f);
    cam.angle = 0.0f;

    // Init object control
    init_object_control();
    // Init stage
    init_stage();
    /// Init hud
    init_hud();

    // Init vpad
    vpad_init();
    
    return 0;
}

/// Update game
/// tm Time multiplier
static void game_update(float tm)
{
    update_obj_control(&cam,tm);
    stage_update(tm);
    hud_update(tm);

    vpad_update();
}

/// Draw game
static void game_draw()
{
    tr_identity();
    use_camera(&cam);

    stage_draw();

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

    hud_draw();
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