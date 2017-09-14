/// Transformation (source)
/// (c) 2017 Jani Nykänen

#include "transform.h"

#include "math.h"

/// Translation
static VEC3 tr;
/// Angle
static float angle;

/// Identitiy model matrix
void tr_identity()
{
    tr.x = 0.0f;
    tr.y = 0.0f;
    tr.z = 0.0f;
    angle = 0.0f;
}

/// Translate model matrix
void tr_translate(float x, float y, float z)
{
    tr.x = x;
    tr.y = y;
    tr.z = z;
}


/// Rotate model matrix
void tr_rotate(float a)
{
    angle += a;
}

/// Return translation
VEC3 tr_get_translation()
{
    return tr;
}

/// Return rotation
float tr_get_angle()
{
    return angle;
}

/// Use transformations for vector p
VEC3 tr_use_transform(VEC3 p)
{

    float s = sin(angle);
    float c = cos(angle);

    // Translate
    VEC3 pt = vec3(p.x+tr.x,p.y+tr.y,p.z+tr.z);

    // Rotate
    float x = pt.x;
    float z = pt.z;
    pt.x = x * c - z * s;
    pt.z = x * s + z * c;

    pt.z *= 0.75f;

    return pt;
}