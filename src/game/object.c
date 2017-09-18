/// Game object, non-player (source)
/// (c) 2017 Jani Nykänen

#include "object.h"

#include "../engine/graphics.h"

/// Create a new object
OBJECT create_object(VEC3 pos, float w, float h)
{
    OBJECT o;

    o.pos = pos;
    o.w = w;
    o.h = h;

    o.exist = false;

    return o;
}

/// Bind texture to an object
void obj_bind_texture(OBJECT* o, BITMAP* tex, VEC2 pos, VEC2 dim)
{
    if(tex != NULL)
    {
        o->texture = tex;
    }
    o->texPos = pos;
    o->texDim = dim;
}

/// Calculate depth value (for object depth buffering)
void obj_calculate_depth(OBJECT* o)
{
    o->depth = tr_use_transform(o->pos).z;
}

/// Map texture area by object angle
/// < o Object
void obj_map_by_angle(OBJECT* o,CAMERA* cam)
{
    float angle = o->angle + cam->angle;

    if(angle >= M_PI*2)
        angle -= M_PI*2;
    else if(angle < 0)
        angle += M_PI*2;

    o->texPos.y = 0.25f * floor(angle / (M_PI/2.0f));
}

/// Draw object
void obj_draw(OBJECT* o)
{
    if(o->texture == NULL) return;

    set_tex_area(o->texPos.x,o->texPos.y,o->texDim.x,o->texDim.y);
    draw_sprite_3D(o->texture,o->pos,o->w,o->h);
}