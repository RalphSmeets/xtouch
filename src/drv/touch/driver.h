#ifndef _XTOUCH_TOUCH_DRIVER_H
#define _XTOUCH_TOUCH_DRIVER_H

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "lvgl.h"

#if TOUCH_DRIVER == 0x2046 
#include "driver_xpt2046.h"
#elif TOUCH_DRIVER == 0x0911
#include "driver_gt911.h"
#endif

#endif