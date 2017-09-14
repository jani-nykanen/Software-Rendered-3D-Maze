/// Main file (source)
/// (c) 2017 Jani Nykänen

#include "engine/app.h"
#include "game/game.h"

/// Main function
/// < argc Argument count
/// < argv Argument values
/// > Error code, 0 on success, 1 on error
int main(int argc, char** argv)
{

    // Set scenes
    SCENE scenes[] = {
        get_game_scene()
    };
    int sceneCount = 1;

    return app_run(scenes,sceneCount);
}