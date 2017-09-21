/// Camera (source)
/// (c) 2017 Jani Nykänen

#include "camera.h"

#include "math.h"

/// Use camera
void use_camera(CAMERA* cam)
{
    if(cam->angle >= M_PI*2)
        cam->angle -= M_PI*2;
    else if(cam->angle < 0)
        cam->angle += M_PI*2;

    tr_rotate(cam->angle);
    tr_translate(cam->pos.x,0.0f,cam->pos.z);
}