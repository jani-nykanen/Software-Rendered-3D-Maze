/// Graphics (source)
/// (c) 2017 Jani Nykänen

#include "graphics.h"

#include "mathext.h"

#include "malloc.h"

/// Global renderer
static SDL_Renderer* grend;
/// Global frame
static FRAME* gframe;
/// Window dim
static SDL_Point windowDim;

/// Wall y translation
static int wallYtrans;
/// Wall view height modifier
static int wallVHeight;

/// Texture used in triangle rendering
static BITMAP* texture;

/// Put pixel to the screen
/// < x X coordinate
/// < y Y coordinate
/// < index Color index
static void put_pixel(int x, int y, Uint8 index)
{
    if(index == 255 || x < 0 || y < 0 || x >= gframe->w || y >= gframe->h) return;

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
    wallYtrans = 0;
    wallVHeight = fr->h;
}

/// Clear frame
void clear_frame(Uint8 index)
{
    memset(gframe->colorData,index,gframe->size);
}

/// Draw a non-scaled bitmap
void draw_bitmap(BITMAP* b, int dx, int dy)
{
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
    
}

/// Draw a scaled bitmap
void draw_scaled_bitmap(BITMAP* b, int dx, int dy, float sx, float sy)
{
    
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
    if(pa.z < 0.1 || pb.z < 0.1) return;

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

    float y3 = wallVHeight/2 - fabs(y1 - wallVHeight/2);
    float y4 = wallVHeight/2 - fabs(y2 - wallVHeight/2);

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

    float tstepx = (float)texture->w / (float)(maxx-minx);
    float tstepy = (float)texture->h / (float)(maxy-miny);

    float tx = 0.0f;
    float ty = 0.0f;

    float depthStart = minf(pa.z,pb.z);
    float depthEnd = maxf(pa.z,pb.z);
    float depthStep = (depthEnd-depthStart) / (float)abs(endx-beginx);

    float depth = cond ? depthStart : depthEnd;

    int x;
    for(x=beginx; x != endx; x += stepx)
    {
        if(x >= 0 && x < gframe->w && depth <= gframe->depth[x] )
        {
            for(dy=starty; dy <= endy; dy += 1.0f)
            {
                put_pixel((int)dx,(int)dy,
                    cond ? texture->data[(int)ty * texture->w + (int)tx ]
                    : texture->data[(int)ty * texture->w + (texture->w - (int)tx  -1)]);
                    
                ty += tstepy;
            }
            gframe->depth[x] = depth;
        }

        starty += stepy  ;
        endy -= stepy ;

        dx -= 1.0f * -stepx;

        tstepy = (float)texture->h / fabs(starty-endy);
        ty = 0.0f;
        tx += tstepx;

        depth += depthStep * stepx;
    }
}

/// Draw a 3D sprite to a position p
void draw_sprite_3D(BITMAP* b, VEC3 p, float w, float h)
{
    // Points on 3D space, no transform
    // After transform
    VEC3 pp = tr_use_transform(p);

    // Too close the camera
    if(pp.z < 0.1) return;

    float xhop = (float)gframe->w / (float) gframe->h;
    float yhop = 1.0f;
    
    // Points on screen
    float fx = pp.x / pp.z +xhop;
    float fy = pp.y / pp.z +yhop;

    fx *= gframe->w / (xhop*2);
    fy *= gframe->h / (yhop*2);

    float sx = 1.0f/pp.z * w;
    float sy = 1.0f/pp.z * h;
    
    int dx = fx - sx * b->w/2;
    int dy = fy - sy * b->h;

    int x; // Screen X
    int y; // Screen Y
    int px = 0; // Pixel X
    int py = 0; // Pixel Y
    float pxf = 0; // Pixel X (float)
    float pyf = 0; // Pixel Y (float)

    float depth = pp.z;

    for(x = dx; x < dx+ (int)floor(b->w * sx); x++)
    {
        if(x >= 0 && x < gframe->w && depth <= gframe->depth[x] )
        {
            for(y = dy; y < dy+ (int)floor(b->h * sy); y++)
            {
                px = (int)(pxf);
                py = (int)(pyf);

                put_pixel(x,y, b->data[py*b->w +px]);
                pyf += 1.0f/sy;
            }

            gframe->depth[x] = depth;
        }
        pyf = 0.0f;
        pxf += 1.0f/sx;
    } 
}

/// Set wall options
void set_wall_options(int ytrans, int viewHeight)
{
    wallYtrans = ytrans;
    wallVHeight = viewHeight;
}

/// Bind texture
void bind_texture(BITMAP* tex)
{
    texture = tex;
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