/// Virtual game pad (header)
/// (c) 2017 Jani Nykänen

#ifndef __VPAD__
#define __VPAD__

#include "engine/controls.h"
#include "engine/transform.h"

/// Initialize virtual gamepad
void vpad_init();

/// Get stick axis
/// > A vector holding stick axis information
VEC2 vpad_get_stick();

/// Update vpad
void vpad_update();

#endif // __VPAD__