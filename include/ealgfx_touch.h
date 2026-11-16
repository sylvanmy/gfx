#ifndef EALGFX_TOUCH_H
#define EALGFX_TOUCH_H

#include <stdint.h>

typedef enum {
    EALGFX_TOUCH_NONE = 0,
    EALGFX_TOUCH_DOWN,
    EALGFX_TOUCH_MOVE,
    EALGFX_TOUCH_UP
} EALGFX_TouchType;

typedef struct {
    EALGFX_TouchType type;
    uint16_t x;
    uint16_t y;
} EALGFX_TouchEvent;

typedef struct {
    uint8_t (*init)(void *user);
    uint8_t (*read)(void *user, uint16_t *x, uint16_t *y, uint8_t *pressed);
    void *user;
} EALGFX_TouchDriver;

typedef struct {
    const EALGFX_TouchDriver *driver;
    uint16_t width, height;
    uint16_t last_x, last_y;
    uint8_t was_pressed;
    uint8_t swap_xy, invert_x, invert_y;
} EALGFX_Touch;

uint8_t EALGFX_TouchAttach(EALGFX_Touch *touch,
                           const EALGFX_TouchDriver *driver,
                           uint16_t width, uint16_t height);
uint8_t EALGFX_TouchInit(EALGFX_Touch *touch);
uint8_t EALGFX_TouchPoll(EALGFX_Touch *touch, EALGFX_TouchEvent *event);
void EALGFX_TouchSetTransform(EALGFX_Touch *touch, uint8_t swap_xy,
                              uint8_t invert_x, uint8_t invert_y);

#endif
