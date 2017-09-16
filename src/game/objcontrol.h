/// Object controller (header)
/// (c) 2017 Jani Nykänen

#ifndef __OBJ_CONTROL__
#define __OBJ_CONTROL__

#include "player.h"

#include "../engine/bitmap.h"

/// Add an object to the game object array
/// < pos Position
/// < w Width
/// < h Height
/// < tex Texture
/// < texArea Texture area
void add_object(VEC3 pos, float w, float h, BITMAP* tex, SDL_Rect texArea);

/// Init object controller
void init_object_control();

/// Update object controller
/// < cam Camera
/// < tm Time mul.
void update_obj_control(CAMERA* cam, float tm);

/// Draw object controller objects
void draw_objects();

#endif // __OBJ_CONTROL__