/// Matrix library (header)
/// (c) 2017 Jani Nykänen

#ifndef __MATRIX__
#define __MATRIX__

/// Vector 3 type
typedef struct
{
    float x,y,z;
}
VEC3;

/// Axes enumerations
enum
{
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2,
};

// TODO: C'mon, macros, seriously?

/// Create new vector 3
/// < x X component
/// < y Y component
/// < z Z component
/// > A new vector 3
#define vec3(x,y,z) (VEC3){x,y,z}

/// Cross product
/// < f Vector f
/// < u Vector u
/// > Cross product vector
#define cross(f,u) (VEC3){ f.y*u.z - f.z*u.y, f.z*u.x - f.x*u.z, f.x*u.y - f.y*u.x }

/// 4x4 matrix type
typedef float MAT4[4][4];

/// Identity matrix
/// < m Matrix where to put identity matrix
void mat4_identity(MAT4 m);

/// Translation matrix
/// < m Matrix out
/// < x X translation
/// < y Y translation
/// < z Z translation
void mat4_translate(MAT4 m, float x, float y, float z);

/// Scale matrix
/// < m Matrix out
/// < x X scale
/// < y Y scale
/// < z Z scale
void mat4_scale(MAT4 m, float x, float y, float z);

/// Rotation matrix
/// < m Matrix 
/// < angle Rotation angle
/// < axis Axis to rotate around
void mat4_rotate(MAT4 m, float angle, int axis);

/// Matrix multiplication
/// < out Matrix output
/// < m1 Operand 1
/// < m2 Operand 2
void mat4_multiply(MAT4 out, MAT4 m1, MAT4 m2);

/// View matrix (@warning: DOES NOT WORK!)
/// < out Matrix output
/// < pos Position
/// < dir Direction
/// < up Up
void mat4_view(MAT4 out, VEC3 pos, VEC3 dir, VEC3 up);

/// Perspective matrix
/// < out Matrix output
/// < left Left value. Right is -left
/// < top Top value. Bottom is -top
/// < near Near value
/// < far Far value
void mat4_perspective(MAT4 out, float left, float top, float near, float far);

/// Multiply matrix with a vector
/// < m Matrix operand
/// < v Vector operand
/// > Result vector
VEC3 mat4_mul_vec3( MAT4 m, VEC3 v);

/// Multiply a matrix with a scalar
/// < out Matrix output
/// < m Matrix operand
/// < scalar Scalar value
void mat4_mul_scalar(MAT4 out, MAT4 m, float scalar);

#endif // __MATRIX__