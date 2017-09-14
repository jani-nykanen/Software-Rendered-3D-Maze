/// Application core (header)
/// (c) 2017 Jani Nykänen

#ifndef __APPLICATION__
#define __APPLICATION__

#include "SDL2/SDL.h"
#include "scene.h"

/// Toggle fullscreen mode
void app_toggle_fullscreen();

/// Initialize application
/// < arrScenes An array of scenes
/// < count Amount of elements in the array
/// > An error code, 0 on success, 1 on error
int app_init(SCENE* arrScenes, int count);

/// Go through events
void app_events();

/// Update application
/// < delta Delta time in milliseconds
void app_update(Uint32 delta);

/// Draw application
void app_draw();

/// Destroy application
void app_destroy();

/// Run application
/// < arrScenes An array of scenes
/// < count Amount of elements in the array
/// > An error code, 0 on success, 1 on error
int app_run(SCENE* arrScenes, int count);

#endif // __APPLICATION__