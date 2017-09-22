/// Door (header)
/// (c) 2017 Jani Nykänen

#include "door.h"

#include "../engine/assets.h"
#include "../engine/graphics.h"

#include "../vpad.h"

/// Door bitmap
static BITMAP* bmpDoor;

/// Initialize doors (mostly init bitmaps)
void init_doors()
{
    bmpDoor = get_bitmap("door");
}

/// Create a door
DOOR create_door(VEC2 pos, bool horizontal, bool locked)
{
    DOOR d;
    d.pos = pos;
    d.horizontal = horizontal;
    d.locked = locked;
    d.opened = false,
    d.angle = 0.0f;
    d.targetAngle = 0.0f;

    float x = d.pos.x;
    float y = d.pos.y;

    if(d.horizontal)
    {
        d.pos1 = vec2( x + 1.0f,y +1.0f);
        d.pos2 = vec2( x+ 1.0f,y +1.0f);
    }
    else
    {
        d.pos1 = vec2( x + 1.0f,y +1.0f);
        d.pos2 = vec2( x+ 1.0f,y +1.0f);
    }

    return d;
}

/// Update the door and also take the player collision
void door_update(DOOR*d, PLAYER* pl, float tm)
{
    float px = -pl->pos.x;
    float py = -pl->pos.y;

    if(vpad_get_button(2) == PRESSED)
    {
            if( (d->horizontal && px > d->pos.x-0.5f && px < d->pos.x+2.5f
             && fabs(py-d->pos.y-1.0f) < 1.5f)
            || (!d->horizontal && py > d->pos.y-0.5f && py < d->pos.y+2.5f
                && fabs(px-d->pos.x-1.0f) < 1.5f) )
             {
                 d->opened = !d->opened;

                 if(d->opened)
                 {
                    d->targetAngle = M_PI / 2.0f * ( (d->horizontal && py-(d->pos.y+1.0f) < 0.0f ) ||
                    (!d->horizontal && px-(d->pos.x+1.0f) < 0.0f )  ? 1 : -1);
                 }
                 else
                 {
                    d->targetAngle = 0.0f;
                 }
             }
    }

    // Angles
    if(d->targetAngle > d->angle)
    {
        d->angle += 0.05f * tm;
        if(d->angle > d->targetAngle)
            d->angle = d->targetAngle;
    }
    else if(d->targetAngle < d->angle)
    {
        d->angle -= 0.05f * tm;
        if(d->angle < d->targetAngle)
            d->angle = d->targetAngle;
    }

    // Collisions
    // @todo Move to another functions
    if(!d->opened)
    {
        if(d->horizontal)
        {
            player_get_collision(pl,vec2(-(d->pos.x+2.0f),-d->pos.y - 1.0f) ,2.0f,true);
        }
        else
        {
            player_get_collision(pl,vec2(-(d->pos.x) -1.0f,-d->pos.y - 2.0f) ,2.0f,false);
        }
    }

    // Set door positions
    if(d->horizontal)
    {
        d->pos1 = vec2(d->pos.x + cos(d->angle) * 1.0f, d->pos.y+1.0f + sin(d->angle) * 1.0f);
        d->pos2 = vec2(d->pos.x+2.0f - cos(-d->angle ) * 1.0f, d->pos.y+1.0f - sin(-d->angle) * 1.0f);
    }
    else
    {
        d->pos1 = vec2(d->pos.x+1.0f + sin(d->angle) * 1.0f, d->pos.y+ cos(d->angle) * 1.0f);
        d->pos2 = vec2(d->pos.x+1.0f - sin(-d->angle ) * 1.0f, d->pos.y+2.0f - cos(-d->angle) * 1.0f);
    }
}

/// Draw door
void door_draw(DOOR*d, CAMERA* cam)
{
    bind_texture(bmpDoor);
    set_tex_area(0.0f,0.0f,0.5f,1.0f);

    float x = d->pos.x;
    float y = d->pos.y;

    if(d->horizontal)
    {
        draw_wall(vec2(x,y+1.0f),d->pos1,1.5f);
        draw_wall(vec2(x +2.0f,y+1.0f),d->pos2,1.5f);
    }
    else
    {
        draw_wall(vec2(x+1.0f,y),d->pos1,1.5f);
        draw_wall(vec2(x+1.0f,y+2.0f),d->pos2,1.5f);
    }
}