#ifndef SETUP_H
#define SETUP_H

#include <pokeagb/pokeagb.h>

#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))

extern void CpuFastSet(void* src, void* dst, u32 mode);

extern void handlers_clear();

extern void c2_dexnav_gui();


extern void reset_pal_settings();


extern void reset_bg_settings();

extern void reset_boxes();

extern void setup();
#endif