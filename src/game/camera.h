/// Camera (header)
/// (c) 2017 Jani Nykänen

#ifndef __CAMERA__
#define __CAMERA__

#include "../engine/transform.h"

/// Camera object
typedef struct
{
    VEC3 pos; /// Position
    float angle; /// Angle
}
CAMERA;

/// Use camera
/// < cam Camera to use
void use_camera(CAMERA* cam);

#endif // __CAMERA__