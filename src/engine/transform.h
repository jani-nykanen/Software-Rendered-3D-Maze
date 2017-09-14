/// Transformation (source)
/// (c) 2017 Jani Nykänen

#ifndef __TRANSFORM__
#define __TRANSFORM__

/// Vector 3 type
typedef struct
{
    float x,y,z;
}
VEC3;

/// Create new vector 3
/// < x X component
/// < y Y component
/// < z Z component
/// > A new vector 3
#define vec3(x,y,z) (VEC3){x,y,z}

/// Vector 2 type
typedef struct
{
    float x,y;
}
VEC2;

/// Create new vector 2
/// < x X component
/// < y Y component
/// > A new vector 2
#define vec2(x,y) (VEC2){x,y}

/// Identity
void tr_identity();

/// Translate
/// < x X coordinate
/// < y Y coordinate
/// < z Z coordinate
void tr_translate(float x, float y, float z);

/// Rotate
/// < angle Rotation angle
void tr_rotate(float angle);

/// Return translation
/// > Translation vector
VEC3 tr_get_translation();

/// Return rotation
/// > Rotation vector
float tr_get_angle();

/// Use transformations for vector p
/// < p Vector
/// > A transformed vector
VEC3 tr_use_transform(VEC3 p);

#endif // __TRANSFORM__