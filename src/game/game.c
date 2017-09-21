/// Game scene (source)
/// (c) 2017 Jani Nykänen

#include "game.h"

#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/transform.h"
#include "../engine/controls.h"
#include "../engine/assets.h"
#include "../engine/tilemap.h"

#include "camera.h"
#include "objcontrol.h"
#include "stage.h"
#include "hud.h"

#include "../vpad.h"

/// Game camera
static CAMERA cam;

/// Init game
static int game_init()
{
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
    // TODO: Move to somewhere else, maybe?
    vpad_init();
    vpad_add_button(0,(int)SDL_SCANCODE_LCTRL,0);
    vpad_add_button(1,(int)SDL_SCANCODE_LSHIFT,1);
    
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

    set_darkness(true,4.0f,8.0f);
    stage_draw(&cam);
    draw_objects();
    set_darkness(false,4.0f,8.0f);

    hud_draw();
}

/// Destroy game
static void game_destroy()
{
    destroy_assets();
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