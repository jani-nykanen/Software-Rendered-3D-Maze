/// HUD (source)
/// (c) 2017 Jani Nykänen

#include "hud.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

/// HUD box
static BITMAP* bmpHudBox;
/// HUD text
static BITMAP* bmpHudText;
/// HUD elem
static BITMAP* bmpHudElem;

/// Heart beat
static float hbeat;

/// Draw hud text
static void draw_hud_text()
{
    draw_bitmap_region(bmpHudText,0,0,48,9, 2, 194); // Sanity
    draw_bitmap_region(bmpHudText,0,9,48,9, 56, 194); // Heart
    draw_bitmap_region(bmpHudText,0,27,48,9, 144, 194); // Danger
    draw_bitmap_region(bmpHudText,0,18,48,9, 196, 194); // Item
}

/// Draw HUD elements
static void draw_hud_elem()
{
    draw_bitmap_region(bmpHudElem,0,0,64,20,0,202);
    // draw_bitmap_region(bmpHudElem,0,20,26,26,74,197);

    float s = sin(hbeat);
    float sc = 0.9f;
    if(s > 0.0f)
    {
        sc = 0.9f + sin(hbeat) * 0.3f;
    }
    

    int y = -1;
    int x = -1;

    for(; y <= 1; y++)
    {
        for(x = -1; x <= 1; x++)
        {
            if( !(x ==y && x == 0) )
            {
                draw_scaled_bitmap_region(bmpHudElem,26,20,26,26,90-13*sc + x,209-13*sc +y,26*sc,26*sc);
            }
        }
    }

    draw_scaled_bitmap_region(bmpHudElem,0,20,26,26,90-13*sc,209-13*sc,26*sc,26*sc);
}

/// Initialize HUD
void init_hud()
{
    bmpHudBox = get_bitmap("hud");
    bmpHudText = get_bitmap("hudText");
    bmpHudElem = get_bitmap("hudElem");

    hbeat = 0.0f;
}

/// Update HUD
void hud_update(float tm)
{
    hbeat += 0.1f * tm;
}

/// Draw HUD
void hud_draw()
{
    draw_bitmap(bmpHudBox,0,192);
    draw_hud_elem();
    draw_hud_text();
}