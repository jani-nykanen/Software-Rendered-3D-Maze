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
void obj_bind_texture(OBJECT* o, BITMAP* tex, SDL_Rect area)
{
    if(tex != NULL)
    {
        o->texture = tex;
    }
    o->texArea = area;
}

/// Calculate depth value (for object depth buffering)
void obj_calculate_depth(OBJECT* o)
{
    o->depth = tr_use_transform(o->pos).z;
}

/// Draw object
void obj_draw(OBJECT* o)
{
    draw_sprite_3D(o->texture,o->pos,o->w,o->h);
}