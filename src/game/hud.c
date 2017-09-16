/// HUD (source)
/// (c) 2017 Jani Nykänen

#include "hud.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

/// HUD box
static BITMAP* bmpHudBox;

/// Initialize HUD
void init_hud()
{
    bmpHudBox = get_bitmap("hud");
}

/// Update HUD
void hud_update(float tm)
{

}

/// Draw HUD
void hud_draw()
{
    draw_bitmap(bmpHudBox,0,192);
}