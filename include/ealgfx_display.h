#ifndef EALGFX_DISPLAY_H
#define EALGFX_DISPLAY_H

#include "ealgfx_types.h"

/* Hardware driver contract. The library owns no NT35510/FSMC knowledge. */
typedef struct {
    uint16_t width;
    uint16_t height;
    void (*init)(void *user);
    void (*fill_rect)(void *user, uint16_t x, uint16_t y,
                      uint16_t w, uint16_t h, EALGFX_Color color);
    void (*blit_rgb565)(void *user, uint16_t x, uint16_t y,
                        uint16_t w, uint16_t h, const EALGFX_Color *pixels);
    void *user;
} EALGFX_DisplayDriver;

typedef struct {
    const EALGFX_DisplayDriver *driver;
} EALGFX_Display;

uint8_t EALGFX_DisplayAttach(EALGFX_Display *display,
                             const EALGFX_DisplayDriver *driver);
void EALGFX_DisplayInit(EALGFX_Display *display);
void EALGFX_DisplayClear(EALGFX_Display *display, EALGFX_Color color);

#endif
