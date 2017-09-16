/// Game object, non-player (header)
/// (c) 2017 Jani Nykänen

#ifndef __OBJECT__
#define __OBJECT__

#include "../engine/transform.h"
#include "../engine/bitmap.h"

#include "stdbool.h"

/// Object ob... well, yeah object object
typedef struct
{
    VEC3 pos; /// Position
    float depth; /// Depth value
    BITMAP* texture; /// Texture
    SDL_Rect texArea; /// Rendering area
    float w; /// Width
    float h; /// Height
    bool exist; /// Does the object exist (if false, ignore in depth buffering)
}
OBJECT;

/// Create a new object
/// < pos Position
/// < w Width
/// < h Height
/// > A new object
OBJECT create_object(VEC3 pos, float w, float h);

/// Bind texture to an object
/// < tex Texture (pass NULL if you want to edit the texArea)
/// < area Texture area
void obj_bind_texture(OBJECT* o, BITMAP* tex, SDL_Rect area);

/// Calculate depth value (for object depth buffering)
void obj_calculate_depth(OBJECT* o);

/// Draw object
void obj_draw(OBJECT* o);

#endif // __OBJECT__