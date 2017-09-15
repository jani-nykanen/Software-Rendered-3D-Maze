/// Graphics (header)
/// (c) 2017 Jani Nykänen

#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "stdbool.h"

#include "bitmap.h"
#include "frame.h"
#include "transform.h"

/// Flipping enumerations
enum
{
    FLIP_HORIZONTAL = 1,
    FLIP_VERTICAL = 2,
    FLIP_BOTH = 3,
};

/// Set the global renderer
/// < rend Renderer
void set_global_renderer(SDL_Renderer* rend);

/// Returns the global renderer
SDL_Renderer* get_global_renderer();

/// Clear screen
/// < r Red
/// < g Green
/// < b Blue
void clear(unsigned char r, unsigned char g, unsigned char b);

/// Set window dimensions
/// < w Width
/// < h Height
void set_dimensions(int w, int h);

/// Returns window dimensions
/// > Window dimensions
SDL_Point get_dimensions();

/// Bind frame so it can be used globally
/// < fr Frame to bind
void bind_frame(FRAME* fr);

/// Clear frame
/// < index Palette index
void clear_frame(Uint8 index);

/// Draw a non-scaled bitmap
/// < b Bitmap to be drawn
/// < dx X coordinate
/// < dy Y coordinate
void draw_bitmap(BITMAP* b, int dx, int dy);

/// Draw a scaled bitmap
/// < b Bitmap to be drawn
/// < dx X coordinate
/// < dy Y coordinate
/// < sx Scale X
/// < sy Scale Y
void draw_scaled_bitmap(BITMAP* b, int dx, int dy, float sx, float sy);

/// Draw a triangle
/// < x1 X coordinate of the first point
/// < y1 Y coordinate of the first point
/// < x2 X coordinate of the second point
/// < y2 Y coordinate of the second point
/// < x3 X coordinate of the third point
/// < y3 Y coordinate of the third point
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

/// Draw a 3D triangle
/// < a Vertex A
/// < b Vertex B
/// < c Vertex C
void draw_triangle_3d(VEC3 a, VEC3 b, VEC3 c);

/// Draw a wall
/// < a First point on the floor (here y=z)
/// < b Second point on the floor
/// < height Wall height
void draw_wall(VEC2 a, VEC2 b, float height);

/// Draw a 3D sprite to a position p
/// < bmp Bitmap
/// < p Position
/// < w Width
/// < h Height
void draw_sprite_3D(BITMAP* bmp, VEC3 p, float w, float h);

/// Fill rectangle
/// < x X coordinate
/// < y Y coordinate
/// < w Width
/// < h Height
/// < index Color index
void fill_rect(int x, int y, int w, int h, Uint8 index);

/// Set floor level (0 by default)
/// < level Floor level
void set_floor_level(int level);

/// Bind texture
/// < tex Texture to bind
void bind_texture(BITMAP* tex);

/// Clear depth buffer
void clear_depth();

#endif // __GRAPHICS__