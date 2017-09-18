/// Game object, non-player (header)
/// (c) 2017 Jani Nykänen

#ifndef __OBJECT__
#define __OBJECT__

#include "../engine/transform.h"
#include "../engine/bitmap.h"

#include "camera.h"

#include "stdbool.h"

/// Object ob... well, yeah object object
typedef struct
{
    VEC3 pos; /// Position
    float angle; /// Object angle
    float depth; /// Depth value
    BITMAP* texture; /// Texture
    VEC2 texPos; /// Texture area pos
    VEC2 texDim; /// Texture area dim
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
/// < pos Tex area pos
/// < dim Tex area dim
void obj_bind_texture(OBJECT* o, BITMAP* tex, VEC2 pos, VEC2 dim);

/// Calculate depth value (for object depth buffering)
void obj_calculate_depth(OBJECT* o);

/// Map texture area by object angle
/// < o Object
void obj_map_by_angle(OBJECT* o, CAMERA* cam);

/// Draw object
void obj_draw(OBJECT* o);

#endif // __OBJECT__