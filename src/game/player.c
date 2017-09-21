/// Player object (source)
/// (c) 2017 Jani Nykänen

#include "player.h"

#include "../vpad.h"

/// Control player
/// < pl Player to control
/// < tm Time mul.
static void pl_control(PLAYER* pl, float tm)
{
    VEC2 stick = vpad_get_stick();
    
    pl->turnSpeed = (pl->running ? 0.05f : (pl->crouch ? 0.02f : 0.04f));

    // Rotate
    if(fabs(stick.x) > 0.1f)
    {
        pl->angle += stick.x * pl->turnSpeed * tm;
    }
    if(pl->angle < 0.0f) pl->angle += M_PI*2;
    else if(pl->angle >= M_PI*2) pl->angle -= M_PI*2;

    if(fabs(stick.y) > 0.1f)
    {
        pl->target.y = stick.y * cos(pl->angle) * pl->maxSpeed ;
        pl->target.x = stick.y * sin(pl->angle) * pl->maxSpeed ;
    }
    else
    {
        pl->target.x = 0.0f;
        pl->target.y = 0.0f;
    }

    pl->crouch = vpad_get_button(0);
    pl->running = vpad_get_button(1);

    if(pl->crouch)
    {
        pl->maxSpeed = 0.02f;
    }
    else
    {
        pl->maxSpeed = pl->running ? 0.1f : 0.04f;
    }

}

/// Move player
/// < pl Player object
/// < tm Time mul.
static void pl_move(PLAYER* pl, float tm)
{
    if(pl->target.x > pl->speed.x)
    {
        pl->speed.x += pl->speedMul * tm;
        pl->speed.x = pl->speed.x > pl->target.x ? pl->target.x : pl->speed.x;
    }
    else if(pl->target.x < pl->speed.x)
    {
        pl->speed.x -= pl->speedMul * tm;
        pl->speed.x = pl->speed.x < pl->target.x ? pl->target.x : pl->speed.x;
    }

    if(pl->target.y > pl->speed.y)
    {
        pl->speed.y += pl->speedMul * tm;
        pl->speed.y = pl->speed.y > pl->target.y ? pl->target.y : pl->speed.y;
    }
    else if(pl->target.y < pl->speed.y)
    {
        pl->speed.y -= pl->speedMul * tm;
        pl->speed.y = pl->speed.y < pl->target.y ? pl->target.y : pl->speed.y;
    }

    pl->pos.x += pl->speed.x * tm;
    pl->pos.y += pl->speed.y * tm;

    pl->totalSpeed = hypot(pl->speed.x,pl->speed.y);

    if(pl->running)
    {
        pl->bumpTimer += 0.125f *tm;
    }
}

/// Create a player object (mostly set default values)
PLAYER create_player(VEC2 pos)
{
    PLAYER pl;
    pl.pos = pos;
    pl.speed = vec2(0.0f,0.0f);
    pl.target = pl.speed;
    pl.angle = 0.0f;
    pl.speedMul = 0.01f;
    pl.maxSpeed = 0.05f;
    pl.turnSpeed = 0.05f;
    pl.radius = 0.95f;
    pl.crouch = false;
    pl.bumpTimer = 0.0f;
    pl.running = false;
    pl.totalSpeed = 0.0f;

    return pl;
}

/// Update player
void player_update(PLAYER* pl, float tm)
{
    pl_control(pl,tm);
    pl_move(pl,tm);
}

/// Set camera to follow player
void player_set_camera(PLAYER* pl, CAMERA* cam, float tm)
{
    if(pl->crouch)
    {
        if(cam->pos.y > -32.0f)
        {
            cam->pos.y -= 2.0f * tm;
            if(cam->pos.y < -32.0f)
            {
                cam->pos.y = -32.0f;
            }
        }
    }
    else if(cam->pos.y < 0.0f)
    {
        cam->pos.y += 2.0f * tm;
        if(cam->pos.y > 0)
        {
            cam->pos.y = 0;
        }
    }
    else
    {
        if(pl->running && pl->totalSpeed > 0.01f)
        {
            cam->pos.y = 0.0f + fabs(sin(pl->bumpTimer)) * 8.0f;
        }
    }

    cam->pos = vec3(pl->pos.x,cam->pos.y,pl->pos.y);
    cam->angle = pl->angle;
}

/// Get (wall) collision
void player_get_collision(PLAYER*pl, VEC2 p, float w, bool horizontal)
{
    if(horizontal)
    {
        if(pl->pos.x+pl->radius/2.0f < p.x || pl->pos.x-pl->radius/2.0f > p.x+w) return;

        float dist = pl->pos.y - p.y;

        if(fabs(dist) < pl->radius && ( (pl->speed.y > 0.0 && dist < 0.0) || (pl->speed.y < 0.0 && dist > 0.0)) )
        {
            pl->pos.y = p.y + pl->radius * (dist <= 0 ? -1 : 1);
            pl->speed.y = 0.0f;
        }
    }
    else
    {
        if(pl->pos.y+pl->radius/2.0f < p.y || pl->pos.y-pl->radius/2.0f > p.y+w) return;
        
        float dist = pl->pos.x - p.x;
        
        if(fabs(dist) < pl->radius && ( (pl->speed.x > 0.0 && dist < 0.0) || (pl->speed.x < 0.0 && dist > 0.0)) )
        {
            pl->pos.x = p.x + pl->radius * (dist <= 0 ? -1 : 1);
            pl->speed.x = 0.0f;
        }
    }
}