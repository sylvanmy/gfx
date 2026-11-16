#ifndef EALGFX_TYPES_H
#define EALGFX_TYPES_H

#include <stdint.h>

typedef uint16_t EALGFX_Color;

typedef struct { int16_t x, y; } EALGFX_Point2i;
typedef struct { float x, y; } EALGFX_Vec2;
typedef struct { float x, y, z; } EALGFX_Vec3;
typedef struct { float m[4][4]; } EALGFX_Mat4;
typedef struct { int16_t x, y, w, h; } EALGFX_Rect;

#define EALGFX_RGB565(r,g,b) ((EALGFX_Color)((((uint16_t)(r)&0xF8U)<<8) | (((uint16_t)(g)&0xFCU)<<3) | ((uint16_t)(b)>>3)))
#define EALGFX_BLACK   ((EALGFX_Color)0x0000U)
#define EALGFX_WHITE   ((EALGFX_Color)0xFFFFU)
#define EALGFX_RED     ((EALGFX_Color)0xF800U)
#define EALGFX_GREEN   ((EALGFX_Color)0x07E0U)
#define EALGFX_BLUE    ((EALGFX_Color)0x001FU)
#define EALGFX_YELLOW  ((EALGFX_Color)0xFFE0U)
#define EALGFX_CYAN    ((EALGFX_Color)0x07FFU)

#endif
