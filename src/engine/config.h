/// Configuration file (header)
/// (c) 2017 Jani Nykänen

#ifndef __CONFIG__
#define __CONFIG__

/// Configuration type
typedef struct
{
    int winWidth; /// Default window width
    int winHeight; /// Default window height
    int fps; /// Maximum fps
    int fullscreen; /// Fullscreen enabled
}
CONFIG;

#endif // __CONGIF__