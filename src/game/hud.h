/// HUD (header)
/// (c) 2017 Jani Nykänen

#ifndef __HUD__
#define __HUD__

/// Initialize HUD
void init_hud();

/// Update HUD
/// < tm Time mul.
void hud_update(float tm);

/// Draw HUD
void hud_draw();

/// Set heart speed
/// < Speed
void hud_set_heart_speed(float s);

#endif // __HUD__