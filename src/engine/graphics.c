/// Graphics (source)
/// (c) 2017 Jani Nykänen

#include "graphics.h"

#include "mathext.h"

#include "malloc.h"

/// Min delta
static const float DEPTH_MIN = 0.025f;

/// Global renderer
static SDL_Renderer* grend;
/// Global frame
static FRAME* gframe;
/// Window dim
static SDL_Point windowDim;

/// Floor level
static int floorLevel;

/// Darkness value
static int darkness;
/// Use darkness
static bool useDarkness;
/// Dark begin
static float darkBegin;
/// Dark end
static float darkEnd;
/// Darkness step
static float darkStep;

/// Texture used in wall rendering
static BITMAP* texture;
/// Wall lines
static bool wallLines[4];
/// Wall tex area pos
static VEC2 texPos;
/// Wall tex area dimensions
static VEC2 texDim;

/// Put pixel to the screen
/// < x X coordinate
/// < y Y coordinate
/// < index Color index
static void put_pixel(int x, int y, Uint8 index)
{
    if(index == 255 || x < 0 || y < 0 || x >= gframe->w || y >= gframe->h) return;

    if(useDarkness)
    {
        Uint8 col;
        if(darkness % 2 == 0)
        {
            col = index  + (darkness+1)/2 *64;
        }
        else
        {
            if( (x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1) )
                col = index  + (darkness)/2 *64;
            else
                col = index  + (darkness+2) / 2 *64;
        }
        gframe->colorData[y*gframe->w+x] = col;
        return;
    }
    gframe->colorData[y*gframe->w+x] = index;
}

/// Set global renderer
void set_global_renderer(SDL_Renderer* rend)
{
    grend = rend;
}

/// Get grend
SDL_Renderer* get_global_renderer()
{
    return grend;
}

/// Clear screen
void clear(unsigned char r, unsigned char g, unsigned char b)
{
    SDL_SetRenderDrawColor(grend, r,g,b, 255);
    SDL_RenderClear(grend);
}

/// Set window dimensions
void set_dimensions(int w, int h)
{
    windowDim.x = w;
    windowDim.y = h;
}

/// Get window dimensions
SDL_Point get_dimensions()
{
    return windowDim;
}

/// Bind frame
void bind_frame(FRAME* fr)
{
    gframe = fr; 
    floorLevel = 0;
    darkness = 0;
}

/// Clear frame
void clear_frame(Uint8 index)
{
    memset(gframe->colorData,index,gframe->size);
}

/// Draw a non-scaled bitmap
void draw_bitmap(BITMAP* b, int dx, int dy)
{
    dy -= floorLevel;

    bool d = useDarkness;
    useDarkness = false;

    int x; // Screen X
    int y = dy; // Screen Y
    int px = 0; // Pixel X
    int py = 0; // Pixel Y

    // Go though every pixel and put them to a frame
    for(; y < dy+b->h; y++)
    {
        for(x = dx; x < dx+b->w; x++)
        {
            put_pixel(x,y, b->data[py*b->w +px]);
            px ++;
        }
        py ++;
        px = 0;
    } 
 
    useDarkness = d;
}

/// Draw a bitmap region
void draw_bitmap_region(BITMAP* b, int sx, int sy, int sw, int sh, int dx, int dy)
{
    dy -= floorLevel;

    bool d = useDarkness;
    useDarkness = false;

    int x; // Screen X
    int y = dy; // Screen Y
    int px = sx; // Pixel X
    int py = sy; // Pixel Y

    // Go though every pixel and put them to a frame
    for(; y < dy+sh; y++)
    {
        for(x = dx; x < dx+sw; x++)
        {
            put_pixel(x,y, b->data[py*b->w +px]);
            px ++;
        }
        py ++;
        px = sx;
    } 
 
    useDarkness = d;
}

/// Draw a bitmap region
/// < b Bitmap to be drawn
/// < sx Source X
/// < sy Source Y
/// < sw Source W
/// < sh Source H
/// < dx X coordinate
/// < dy Y coordinate
/// < dw Destination w
/// < dh Destination h
void draw_scaled_bitmap_region(BITMAP* b, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{
    dy -= floorLevel;

    int x; // Screen X
    int y = dy; // Screen Y
    int px = sx; // Pixel X
    int py = sy; // Pixel Y
    float pxf = (float)sx; // Pixel X (float)
    float pyf = (float)sy; // Pixel Y (float)

    float ssx = (float)dw/(float)sw;
    float ssy = (float)dh/(float)sh;

    // Go though every pixel and put them to a frame
    // if pixel is not out of frame range
    for(; y < dy+ (int)floor(dh ); y++)
    {
        for(x = dx; x < dx+ (int)floor(dw ); x++)
        {
            px = (int)(pxf);
            py = (int)(pyf);

            put_pixel(x,y, b->data[py*b->w +px]);
            pxf += 1.0f/ssx;
        }
        pyf += 1.0f/ssy;
        pxf = (float)sx;
    } 
}

/// Draw a scaled bitmap
void draw_scaled_bitmap(BITMAP* b, int dx, int dy, float sx, float sy)
{
    dy -= floorLevel;

    int x; // Screen X
    int y = dy; // Screen Y
    int px = 0; // Pixel X
    int py = 0; // Pixel Y
    float pxf = 0; // Pixel X (float)
    float pyf = 0; // Pixel Y (float)

    // Go though every pixel and put them to a frame
    // if pixel is not out of frame range
    for(; y < dy+ (int)floor(b->h * sy); y++)
    {
        for(x = dx; x < dx+ (int)floor(b->w * sx); x++)
        {
            px = (int)(pxf);
            py = (int)(pyf);

            put_pixel(x,y, b->data[py*b->w +px]);
            pxf += 1.0f/sx;
        }
        pyf += 1.0f/sy;
        pxf = 0;
    } 
    
}

/// Draw text using a bitmap font
void draw_text(BITMAP* b, Uint8* text, int len, int dx, int dy, int xoff, int yoff, bool center)
{
    int x = dx;
    int y = dy;
    int cw = b->w / 16;
    int ch = b->h / 16;
    int i=0;
    Uint8 c;
    int sx;
    int sy;

    for(; i < len && text[i] != '\0'; i++)
    {
        c = text[i];
        sx = c % 16;
        sy = c / 16;

        draw_bitmap_region(b,sx*16,sy*16,cw,ch,x,y);

        x += cw + xoff;
    }
}

/// Draw triangle
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int minx = min(x1,min(x2,x3));
    int miny = min(y1,min(y2,y3));
    int maxx = max(x1,max(x2,x3));
    int maxy = max(y1,max(y2,y3));

    int x;
    int y;
    bool hasStarted = false;

    for(y=miny; y <= maxy; y++)
    {
        for(x=minx; x <= maxx; x++)
        {
            if(inside_triangle(x,y,x1,y1,x2,y2,x3,y3))
            {
                hasStarted = true;
                put_pixel(x,y,0);
            }
            else if(hasStarted)
            {
                hasStarted = false;
                break;
            }
        }
        hasStarted = false;
    }
}

/// Draw triangle 3D
void draw_triangle_3d(VEC3 a, VEC3 b, VEC3 c)
{
    // Translate
    VEC3 pa = tr_use_transform(a);
    VEC3 pb = tr_use_transform(b);
    VEC3 pc = tr_use_transform(c);

    if(pa.z < 0.1 || pb.z < 0.1 || pc.z < 0.1) return;

    float xhop = (float)gframe->w / (float) gframe->h;
    float yhop = 1.0f;

    float x1 = pa.x / pa.z +xhop;
    float y1 = pa.y / pa.z +yhop;
    float x2 = pb.x / pb.z +xhop;
    float y2 = pb.y / pb.z +yhop;
    float x3 = pc.x / pc.z +xhop;
    float y3 = pc.y / pc.z +yhop;

    x1 *= gframe->w / (xhop*2);
    y1 *= gframe->h / (yhop*2);
    x2 *= gframe->w / (xhop*2);
    y2 *= gframe->h / (yhop*2);
    x3 *= gframe->w / (xhop*2);
    y3 *= gframe->h / (yhop*2);

    draw_triangle((int)x1,(int)y1,(int)x2,(int)y2,(int)x3,(int)y3);
}

/// Draw a wall
/// @TODO Check out the final line of the bitmap, make sure no segfaults!
void draw_wall(VEC2 a, VEC2 b, float height)
{
    // Need explanation? Too bad, you won't get any!

    // Points on 3D space, no transform
    VEC3 a3 = vec3(a.x,height/2.0f,a.y);
    VEC3 b3 = vec3(b.x,height/2.0f,b.y);

    // After transform
    VEC3 pa = tr_use_transform(a3);
    VEC3 pb = tr_use_transform(b3);

    // Too close the camera
    if(pa.z < DEPTH_MIN || pb.z < DEPTH_MIN) return;

    float xhop = (float)gframe->w / (float) gframe->h;
    float yhop = 1.0f;
    
    // Points on screen
    float x1 = pa.x / pa.z +xhop;
    float y1 = pa.y / pa.z +yhop;
    float x2 = pb.x / pb.z +xhop;
    float y2 = pb.y / pb.z +yhop;

    x1 *= gframe->w / (xhop*2);
    y1 *= gframe->h / (yhop*2);
    x2 *= gframe->w / (xhop*2);
    y2 *= gframe->h / (yhop*2);

    float y3 = gframe->h/2 - fabs(y1 - gframe->h/2);
    float y4 = gframe->h/2 - fabs(y2 - gframe->h/2);

    int minx = min(x1,x2);
    int miny = min(y3,y4);
    int maxx = max(x1,x2);
    int maxy = max(y1,y2);

    // Not in screen
    if( (minx < 0 && maxx < 0) || (minx >= gframe->w && maxx >= gframe->w) )
    {
        return;
    }

    float stepy =  (y2 - y1) / (x2 - x1);

    bool cond = stepy < 0.0f;

    int beginx = cond ? minx : maxx;
    int endx = cond ? maxx : minx;
    int stepx = cond ? 1 : -1;

    if(cond) stepy *= -1;

    float dx = (float)beginx;
    float dy = (float)miny;

    float starty = miny;
    float endy = maxy;

    int tpx = (int)( texPos.x * texture->w);
    int tpy = (int)( texPos.y * texture->h);
    int tpw = (int)( texDim.x * texture->w);
    int tph = (int)( texDim.y * texture->h);

    float tstepx = (float) (texDim.x * texture->w) / (float)(maxx-minx);
    float tstepy = (float) (texDim.y * texture->h) / (float)(maxy-miny);

    float tx = tpx;
    float ty = tpy;

    float depthStart = minf(pa.z,pb.z);
    float depthEnd = maxf(pa.z,pb.z);
    float depthStep = (depthEnd-depthStart) / (float)abs(endx-beginx);

    float depth = cond ? depthStart : depthEnd;

    // TODO: Make sure this works!
    /*
    if( (!cond ? depthStart : depthEnd) > gframe->depth[minx] 
        && (!cond ? depthEnd : depthStart) > gframe->depth[maxx])
    {
        return;
    }
    */
    
    // Color index
    Uint8 cindex;

    darkness = 0;

    int x;
    for(x=beginx; x - stepx != endx; x += stepx)
    {
        if(x >= 0 && x < gframe->w && (depthStart + depthEnd)/2.0f <= gframe->depth[x] )
        {
            if(useDarkness)
            {
                if(depth >= darkBegin)
                {
                    darkness = floor(6 * (depth - darkBegin) / (darkEnd-darkBegin) ) +1;
                    if(darkness > 6) darkness = 6;
                }
                else
                    darkness = 0;
            }

            for(dy=starty; dy <= endy; dy += 1.0f)
            {
                if(cond)
                    cindex = texture->data[(int)ty * texture->w + (int)tx ];
                else
                    cindex = texture->data[(int)ty * texture->w + (tpw - (int)tx  -1)];
                    
                put_pixel((int)dx,(int)dy - floorLevel,cindex);
                    
                ty += tstepy;
                if((int)ty >= texture->h)
                    ty = texture->h -1.0f;

                if(wallLines[0] && dy + 1.0f >= endy)
                {
                    put_pixel((int)dx,(int)dy - floorLevel + (x == beginx || x == endx ? 0 : 1), 0);
                }
                else if(wallLines[1] && dy - 1.0f < starty)
                {
                    put_pixel((int)dx,(int)dy - floorLevel - (x == beginx || x == endx ? 0 : 1), 0);
                }
            }
            gframe->depth[x] = (depthStart + depthEnd)/2.0f ;
        }

        starty += stepy  ;
        endy -= stepy ;

        dx -= 1.0f * -stepx;

        tstepy = (float)(tph) / fabs(starty-endy);
        ty = tpy;
        tx += tstepx;
        if((int)tx >= texture->w)
            tx = texture->w-1;

        depth += depthStep ;
    }

    if(wallLines[2])
    {
        if( x1 < x2 ? depthStart <= gframe->depth[(int)x1] 
            : depthEnd <= gframe->depth[(int)x1])
            fill_rect(x1,y3 -floorLevel,1,y1-y3+1,0);
    }
    if(wallLines[3])
    {
        if( x1 < x2 ? depthEnd <= gframe->depth[(int)x2] 
            : depthStart <= gframe->depth[(int)x2])
            fill_rect(x2,y4 -floorLevel,1,y2-y4+1,0);
    }
}

/// Draw a 3D sprite to a position p
void draw_sprite_3D(BITMAP* b, VEC3 p, float w, float h)
{
    // Points on 3D space, no transform
    // After transform
    VEC3 pp = tr_use_transform(p);

    // Too close the camera
    if(pp.z < DEPTH_MIN) return;

    float xhop = (float)gframe->w / (float) gframe->h;
    float yhop = 1.0f;
    
    // Points on screen
    float fx = pp.x / pp.z +xhop;
    float fy = pp.y / pp.z +yhop;

    fx *= gframe->w / (xhop*2);
    fy *= gframe->h / (yhop*2);

    float sx = 1.0f/pp.z * w;
    float sy = 1.0f/pp.z * h;

    int tpx = (int)( texPos.x * b->w);
    int tpy = (int)( texPos.y * b->h);

    float stepx = 1.0f/sx * ((b->w*texDim.x)/64.0f);
    float stepy = 1.0f/sy * ((b->h*texDim.y)/64.0f);

    int dx = fx - sx * 32;
    int dy = fy - sy * 64;

    int x; // Screen X
    int y; // Screen Y
    int px = tpx; // Pixel X
    int py = tpy; // Pixel Y
    float pxf = (float)tpx; // Pixel X (float)
    float pyf = (float)tpy; // Pixel Y (float)

    float depth = pp.z;

    if(useDarkness)
    {
        if(depth >= darkBegin)
        {
            darkness = floor(6 * (depth - darkBegin) / (darkEnd-darkBegin) ) +1;
            if(darkness > 6) darkness = 6;
        }
        else
            darkness = 0;
    }

    for(x = dx; x < dx+ 64*sx; x++)
    {
        if(x >= 0 && x < gframe->w && depth <= gframe->depth[x] )
        {
            for(y = dy; y < dy+ 64*sy; y++)
            {
                px = (int)(pxf);
                py = (int)(pyf);

                put_pixel(x,y -floorLevel, b->data[py*b->w +px]);
                pyf += stepy;
            }

            gframe->depth[x] = depth;
        }
        pyf = (float)tpy;
        pxf += stepx;
    } 
}

/// Fill rectangle
void fill_rect(int x, int y, int w, int h, Uint8 index)
{
    int dx = x;
    int dy = y;

    for(; dy < y+h; dy++)
    {
        for(dx = x; dx < x+w; dx++)
        {
            put_pixel(dx,dy,index);
        }
    }
}

/// Draw line
void draw_line(int x1, int y1, int x2, int y2, Uint8 index, float depthStart, float depthStep)
{
    
    int x0 = x1;
    int y0 = y1;
        
    int dx = abs(x2-x0), sx = x0<x2 ? 1 : -1;
    int dy = abs(y2-y0), sy = y0<y2 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    int oldX;
    int stepx = x1 < x2 ? -1 : 1;

    float depth = depthStart;
        
    for(;;)
    {
        oldX = dx;

        if(depth <= gframe->depth[dx])
            put_pixel(x0,y0,index);

        if (x0==x2 && y0==y2) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }

        if(oldX != dx)
            depth += depthStep * stepx;
    }
}

/// Set floor level (0 by default)
/// < level Floor level
void set_floor_level(int level)
{
    floorLevel = level;
}

/// Set wall lines
void set_wall_lines(bool bottom, bool top, bool near, bool far)
{
    wallLines[0] = bottom;
    wallLines[1] = top;
    wallLines[2] = near;
    wallLines[3] = far;
}

/// Set wall texture area
/// < x X coordinate
/// < y Y coordinate
/// < w Width
/// < h Height
void set_tex_area(float x, float y, float w, float h)
{
    texPos.x = x;
    texPos.y = y;
    texDim.x = w;
    texDim.y = h;
}

/// Bind texture
void bind_texture(BITMAP* tex)
{
    texture = tex;
    texPos.x = 0.0f;
    texPos.y = 0.0f;
    texDim.x = 1.0f;
    texDim.y = 1.0f;
}

/// Clear depth buffer
void clear_depth()
{
    int i = 0;
    for(; i < gframe->w; i++)
    {
        gframe->depth[i] = 10000.0f;
    }
}


/// Enabled darkness
void set_darkness(bool use, float begin, float end)
{
    useDarkness = use;
    if(use)
    {
        darkBegin = begin;
        darkEnd = end;
        darkStep = (darkEnd-darkBegin) / 3.0f;
    }
    
    darkness = 0;
}