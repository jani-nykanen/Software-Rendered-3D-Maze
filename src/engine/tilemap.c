/// Tilemap (header)
/// (c) 2017 Jani Nykänen

#include "tilemap.h"

#include "tmx.h"

/// Load a tilemap from a file
TILEMAP* load_tilemap(const char* path)
{
    // Allocate memory
    TILEMAP* t = (TILEMAP*)malloc(sizeof(TILEMAP));
    if(t == NULL)
    {
        printf("Memory allocation error!\n");
        return NULL;
    }

    // Open map file
    tmx_map* map = tmx_load(path);
    if(map == NULL) 
    {
        printf("Failed to open a tilemap in %s!\n",path);
        return NULL;
    }
    
    // Free map as it's no longer needed
    tmx_map_free(map);

    return t;
}
