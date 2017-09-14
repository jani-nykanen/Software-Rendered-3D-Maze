/// Matrix library (source)
/// (c) 2017 Jani Nykänen

#include "mat.h"
#include "math.h"

/// Clear matrix (put 0.0f everywhere)
/// < m Matrix to modify
static void clear_matrix(MAT4 m)
{
    int i = 0;
    int j;
    for(; i < 4; i++)
    {
        for(j=0; j < 4; j++)
        {
            m[i][j] = 0;
        }
    }

}

/// Identity matrix
void mat4_identity(MAT4 m)
{
    clear_matrix(m);

    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
}

/// Translation matrix
void mat4_translate(MAT4 m, float x, float y, float z)
{
    clear_matrix(m);
    
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;

    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

/// Scale matrix
void mat4_scale(MAT4 m, float x, float y, float z)
{
    clear_matrix(m);

    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    m[3][3] = 1;
}

/// Rotation matrix
void mat4_rotate(MAT4 m, float angle, int axis)
{
    clear_matrix(m);
    m[3][3] = 1;

    switch(axis)
    {
        default:
        case AXIS_X:
            m[0][0] = 1;
            m[1][1] = cos(angle);
            m[2][2] = m[1][1];
            m[2][1] = -sin(angle);
            m[1][2] = -m[2][1];
            break;

        case AXIS_Y:
            m[1][1] = 1;
            m[0][0] = cos(angle);
            m[2][2] = m[0][0];
            m[0][2] = -sin(angle);
            m[2][0] = -m[0][2];
            break;

        case AXIS_Z:
            m[2][2] = 1;
            m[0][0] = cos(angle);
            m[1][1] = m[0][0];
            m[1][0] = -sin(angle);
            m[0][1] = -m[1][0];
            break;
    }
}

/// Matrix multiplication
void mat4_multiply(MAT4 out, MAT4 m1, MAT4 m2)
{
    int i;
    int j = 0;

    for(; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            out[i][j] = m2[i][0]*m1[0][j] + m2[i][1]*m1[1][j] + m2[i][2]*m1[2][j] + m2[i][3]*m1[3][j];
        }
    }
}

/// View matrix
void mat4_view(MAT4 out, VEC3 pos, VEC3 dir, VEC3 up)
{
    // DOES NOT WORK!

    VEC3 f;

    f.x = pos.x - dir.x;
    f.y = pos.y - dir.y;
    f.z = pos.z - dir.z;

    // TODO: Euclidean norm function for vec3
    float n = 1.0f / sqrt(f.x*f.x+f.y*f.y+f.z*f.z);

    f.x *= n; f.y *= n; f.z *= n;

    VEC3 s = cross(f,up);
    n = 1.0f / sqrt(s.x*s.x+s.y*s.y+s.z*s.z);

    s.x *= n; s.y *= n; s.z *= n;

    VEC3 v = cross(s,f);

    out[0][0] = s.x; out[0][1] = s.y; out[0][2] = s.z; out[0][3] = 0; 
    out[1][0] = v.x; out[1][1] = v.y; out[1][2] = v.z; out[1][3] = 0; 
    out[2][0] = f.x; out[2][1] = f.y; out[2][2] = f.z; out[2][3] = 0; 
    out[3][0] = pos.x; out[3][1] = pos.y; out[3][2] = pos.z; out[3][3] = 1; 
}

/// Perspective matrix
void mat4_perspective(MAT4 out, float left, float top, float near, float far)
{
    clear_matrix(out);

    out[0][0] = near / left;
    out[1][1] = near / top;
    out[2][2] = -(far + near) / (far - near);
    out[3][2] = -2 * far * near / (far - near);
    out[2][3] = -1;
}

/// Multiply matrix with a vector
VEC3 mat4_mul_vec3(MAT4 m, VEC3 v)
{
    return vec3(
        m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
        m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
        m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]
    );
}

/// Multiply with scalar
void mat4_mul_scalar(MAT4 out, MAT4 m, float scalar)
{
    int j = 0;
    int i;
    for(; j < 4; j++)
    {
        for(i=0; i < 4; i++)
        {
            out[i][j] = scalar * m[i][j];
        }
    }
}