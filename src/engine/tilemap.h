/// Tilemap (header)
/// (c) 2017 Jani Nykänen

#ifndef __TILEMAP__
#define __TILEMAP__

#include "SDL2/SDL.h"

/// Tilemap structure
typedef struct
{
    int w; /// Width
    int h; /// Height
    Uint8* layers[16]; /// Layers
}
TILEMAP;

/// Load a tilemap from a file (tmx format)
/// < path Tilemap path
/// > A new tilemap
TILEMAP* load_tilemap(const char* path);

#endif // __TILEMAP__