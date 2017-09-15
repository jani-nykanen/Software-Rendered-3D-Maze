/// Application core (header)
/// (c) 2017 Jani Nykänen

#ifndef __APPLICATION__
#define __APPLICATION__

#include "SDL2/SDL.h"
#include "scene.h"

/// Toggle fullscreen mode
void app_toggle_fullscreen();

/// Run application
/// < arrScenes An array of scenes
/// < count Amount of elements in the array
/// < assPath Assets list path
/// > An error code, 0 on success, 1 on error
int app_run(SCENE* arrScenes, int count);

#endif // __APPLICATION__