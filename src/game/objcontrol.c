/// Object controller (source)
/// (c) 2017 Jani Nykänen

#include "objcontrol.h"

#include "stage.h"
#include "object.h"

#include "../engine/assets.h"

#define NUM_OBJ 32
#define NUM_DOORS 32

/// Figure texture
static BITMAP* bmpFigure;
/// Plant bitmap
static BITMAP* bmpPlant;
/// Baby bitmap
static BITMAP* bmpBaby;

/// Player object
static PLAYER pl;
/// Non-player game objects
static OBJECT objs[NUM_OBJ];
/// Object render order
static int objDepth[NUM_OBJ];
/// Object count
static int objCount;
/// Doors
static DOOR doors[32];
/// Door count
static int doorCount;

/// Put the objects in order by the depth values!
static void sort_depth()
{
    int loop = 0;
    int i;
    int i2;
    float maxv;
    int maxid;

    for(i=0; i < NUM_OBJ; i ++)
    {
        objDepth[i] = -1;
    }

    for(loop = 0; loop < NUM_OBJ; loop ++)
    {
        maxv = -9999.0f;
        maxid = -1;
        for(i=0; i < NUM_OBJ; i++)
        {
            if(objs[i].exist == false)
            {
                break;
            }

            if(objs[i].depth >= maxv)
            {
                bool inList = false;
                for(i2=0; i2 < NUM_OBJ; i2++)
                {
                    if(objs[i2].exist == false)
                    {
                        break;
                    }

                    if(objDepth[i2] == i)
                    {
                        inList = true;
                        break;
                    }
                }

                if(!inList)
                {
                    maxv = objs[i].depth;
                    maxid = i;
                }
            }
        }
        if(maxid >= 0)
        {
            objDepth[loop] = maxid;
        }
        else
        {
            return;
        }

    }
}

/// Add an object to the game object array
void add_object(VEC3 pos, float w, float h, BITMAP* tex)
{
    int i = 0;
    for(; i < NUM_OBJ; i++)
    {
        if(objs[i].exist == false)
        {
            objs[i] = create_object(pos,w,h);
            obj_bind_texture(&objs[i],tex,vec2(0.0f,0.0f),vec2(1.0f,1.0f));
            objs[i].exist = true;

            objCount ++;

            return;
        }
    }
    
}

/// Add a door
void add_door(VEC2 pos, bool horizontal, bool locked)
{
    if(doorCount >= NUM_DOORS)
    {
        printf("No more room for doors!\n");
        return;
    }

    doors[doorCount] = create_door(pos,horizontal,locked);
    doorCount ++;
}

/// Init object controller
void init_object_control()
{
    pl = create_player(vec2(-2.0f,-2.0f));

    int i = 0;
    for(; i < NUM_OBJ; i++)
    {
        objs[i].exist = false;
    }

    // Get required bitmaps
    bmpFigure = get_bitmap("figure");
    bmpPlant = get_bitmap("plant");
    bmpBaby = get_bitmap("baby");

    // Init doors
    init_doors();

    objCount = 0;
    doorCount = 0;

    // Add test objects
    add_object(vec3(0.5f,1.0f,2.0f),2.0f,2.0f,bmpFigure);
    add_object(vec3(1.5f,1.0f,0.5f),2.0f,2.0f,bmpFigure);
    add_object(vec3(2.25f,1.0f,1.25f),2.0f,2.0f,bmpFigure);
    add_object(vec3(4.0f,1.0f,16.5f),2.0f,3.0f,bmpPlant);
    add_object(vec3(6.0f,1.0f,2.5f),1.25f,2.5f,bmpBaby);

    for(i=0; i < 3; i++)
    {
        objs[i].texPos = vec2(0.0f,0.0f);
        objs[i].texDim = vec2(1.0f,0.25f);
        objs[i].angle = M_PI/2.0f * (float) (rand() % 4);
    }
}

/// Update object controller
void update_obj_control(CAMERA* cam, float tm)
{
    player_update(&pl,tm);
    stage_get_player_collision(&pl);
    player_set_camera(&pl,cam,tm);

    // Update doors
    int i;
    for(i = 0; i < doorCount; i++)
    {
        door_update(&doors[i],&pl,tm);
    }

    // Calculate obj depth
    for(i=0; i < objCount; i++)
    {
        if(objs[i].exist)
        {
            obj_calculate_depth(&objs[i]);

            if(i < 3)
            {
                obj_map_by_angle(&objs[i],cam);
            }
        }
    }

    // Sort by depth
    sort_depth();
}

/// Draw object controller objects
void draw_objects(CAMERA* cam)
{
    int i = 0;

    // Draw doors
    for(i = 0; i < doorCount; i++)
    {
        door_draw(&doors[i],cam);
    }

    // Draw objects
    for(i=0; i < objCount; i++)
    {
        if(objDepth[i] < 0)
        {
            break;
        }

        if(objs[objDepth[i]].exist)
        {
            obj_draw(&objs[objDepth[i]]);
        }
    }
}