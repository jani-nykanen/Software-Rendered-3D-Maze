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
/// Font 16
static BITMAP* bmpFont16;
/// Time (temporarily here)
static float gameTime;
/// Time string
static Uint8 timeString [16];

/// Heart beat
static float hbeat;

/// Set time string
static void set_time_string()
{   
    timeString[0] = 48+ (int)floor(gameTime/ 3600.0f);
    timeString[1] = ':';
    float sec = (float) ( (int)floor(gameTime/60.0f) % 60 );
    timeString[2] = 48+  (int)floor(sec / 10.0f);
    timeString[3] = 48+ ((int)sec - 10* (int)floor(sec / 10.0f));
    timeString[4] = '\0'; 
}

/// Draw hud text
static void draw_hud_text()
{
    draw_bitmap_region(bmpHudText,0,0,48,9, 2, 194); // Sanity
    draw_bitmap_region(bmpHudText,0,9,48,9, 56, 194); // Heart
    draw_bitmap_region(bmpHudText,0,27,48,9, 144, 194); // Time
    draw_bitmap_region(bmpHudText,0,18,48,9, 196, 194); // Item

    // Draw time text
    set_time_string();

    draw_text(bmpFont16,timeString,16,146,204,-7,0,false);
}

/// Draw HUD elements
static void draw_hud_elem()
{
    // Draw sanity
    draw_bitmap_region(bmpHudElem,0,0,64,20,0,202);

    // Draw heart
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

    // Draw items
    draw_bitmap_region(bmpHudElem,64,0,20,20,190,202);
    draw_bitmap_region(bmpHudElem,64,20,20,20,220,202);

    draw_text(bmpFont16,(Uint8*)"x0",2,198,212,-7,0,false);
    draw_text(bmpFont16,(Uint8*)"x0",2,228,212,-7,0,false);
}

/// Initialize HUD
void init_hud()
{
    bmpHudBox = get_bitmap("hud");
    bmpHudText = get_bitmap("hudText");
    bmpHudElem = get_bitmap("hudElem");
    bmpFont16 = get_bitmap("font16");

    hbeat = 0.0f;

    gameTime = 60*60*2;
}

/// Update HUD
void hud_update(float tm)
{
    hbeat += 0.1f * tm;
    gameTime -= 1.0f * tm;
}

/// Draw HUD
void hud_draw()
{
    set_floor_level(0);

    draw_bitmap(bmpHudBox,0,192);
    draw_hud_elem();
    draw_hud_text();
}