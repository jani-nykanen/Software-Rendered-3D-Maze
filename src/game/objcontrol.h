/// Object controller (header)
/// (c) 2017 Jani Nykänen

#ifndef __OBJ_CONTROL__
#define __OBJ_CONTROL__

#include "player.h"
#include "door.h"

#include "../engine/bitmap.h"

/// Add an object to the game object array
/// < pos Position
/// < w Width
/// < h Height
/// < tex Texture
void add_object(VEC3 pos, float w, float h, BITMAP* tex);

/// Add a door
/// < pos Door pos
/// < locked Is the door locked
/// < horizontal Is the door horizontal
void add_door(VEC2 pos, bool horizontal, bool locked);

/// Init object controller
void init_object_control();

/// Update object controller
/// < cam Camera
/// < tm Time mul.
void update_obj_control(CAMERA* cam, float tm);

/// Draw object controller objects
/// < cam Camera
void draw_objects(CAMERA* cam);

#endif // __OBJ_CONTROL__