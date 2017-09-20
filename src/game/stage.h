/// Stage (header)
/// (c) 2017 Jani Nykänen

#ifndef __STAGE__
#define __STAGE__

#include "player.h"

/// Initialize stage
void init_stage();

/// Update stage
/// < tm Time multiplier
void stage_update(float tm);

/// Get player collision
/// < pl Player
void stage_get_player_collision(PLAYER* pl);

/// Draw stage
void stage_draw(CAMERA* cam);

#endif // __STAGE__