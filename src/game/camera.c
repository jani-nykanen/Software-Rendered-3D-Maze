/// Camera (source)
/// (c) 2017 Jani Nykänen

#include "camera.h"

/// Use camera
void use_camera(CAMERA* cam)
{
    tr_rotate(cam->angle);
    tr_translate(cam->pos.x,cam->pos.y,cam->pos.z);
}