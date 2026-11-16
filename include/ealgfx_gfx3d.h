#ifndef EALGFX_GFX3D_H
#define EALGFX_GFX3D_H

#include "ealgfx_gfx2d.h"
#include "ealgfx_math.h"

typedef struct { uint16_t a, b; } EALGFX_Edge;
typedef struct {
    const EALGFX_Vec3 *vertices;
    uint16_t vertex_count;
    const EALGFX_Edge *edges;
    uint16_t edge_count;
} EALGFX_WireMesh;

typedef struct {
    float rotation_x, rotation_y, rotation_z;
    float distance;
    float focal_length;
    int16_t center_x, center_y;
} EALGFX_Camera3D;

uint8_t EALGFX_ProjectPoint(EALGFX_Vec3 point, const EALGFX_Camera3D *camera,
                            EALGFX_Point2i *screen);
void EALGFX_DrawWireMesh(EALGFX_Surface *surface, const EALGFX_WireMesh *mesh,
                         const EALGFX_Camera3D *camera, EALGFX_Color color);
const EALGFX_WireMesh *EALGFX_BuiltinCube(void);

#endif
