/// Object controller (header)
/// (c) 2017 Jani Nykänen

#ifndef __OBJ_CONTROL__
#define __OBJ_CONTROL__

#include "player.h"

/// Init object controller
void init_object_control();

/// Update object controller
/// < cam Camera
/// < tm Time mul.
void update_obj_control(CAMERA* cam, float tm);

#endif // __OBJ_CONTROL__