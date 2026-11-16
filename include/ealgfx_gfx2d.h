#ifndef EALGFX_GFX2D_H
#define EALGFX_GFX2D_H

#include "ealgfx_display.h"

/* A render target may be an LCD, strip buffer, region buffer or host image. */
typedef struct EALGFX_Surface EALGFX_Surface;
typedef void (*EALGFX_SurfaceFillRect)(EALGFX_Surface *surface,
                                       int x, int y, int w, int h,
                                       EALGFX_Color color);

struct EALGFX_Surface {
    int16_t width, height;
    EALGFX_Rect clip;
    EALGFX_SurfaceFillRect fill_rect;
    void *user;
};

void EALGFX_SurfaceFromDisplay(EALGFX_Surface *surface, EALGFX_Display *display);
void EALGFX_SurfaceSetClip(EALGFX_Surface *surface, EALGFX_Rect clip);
void EALGFX_SurfaceResetClip(EALGFX_Surface *surface);
void EALGFX_Pixel(EALGFX_Surface *s, int x, int y, EALGFX_Color color);
void EALGFX_Clear(EALGFX_Surface *s, EALGFX_Color color);
void EALGFX_FillRect(EALGFX_Surface *s, int x, int y, int w, int h, EALGFX_Color color);
void EALGFX_Rectangle(EALGFX_Surface *s, int x, int y, int w, int h, EALGFX_Color color);
void EALGFX_Line(EALGFX_Surface *s, int x0, int y0, int x1, int y1, EALGFX_Color color);
void EALGFX_Circle(EALGFX_Surface *s, int cx, int cy, int radius, EALGFX_Color color);
void EALGFX_FillCircle(EALGFX_Surface *s, int cx, int cy, int radius, EALGFX_Color color);
void EALGFX_Triangle(EALGFX_Surface *s, EALGFX_Point2i a, EALGFX_Point2i b,
                     EALGFX_Point2i c, EALGFX_Color color);

#endif
