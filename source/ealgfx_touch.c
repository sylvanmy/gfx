#include "ealgfx_touch.h"

uint8_t EALGFX_TouchAttach(EALGFX_Touch *touch,
                           const EALGFX_TouchDriver *driver,
                           uint16_t width, uint16_t height)
{
    if (!touch || !driver || !driver->read || !width || !height) return 0U;
    touch->driver = driver;
    touch->width = width;
    touch->height = height;
    touch->last_x = touch->last_y = 0U;
    touch->was_pressed = 0U;
    touch->swap_xy = touch->invert_x = touch->invert_y = 0U;
    return 1U;
}

uint8_t EALGFX_TouchInit(EALGFX_Touch *touch)
{
    if (!touch || !touch->driver) return 0U;
    return touch->driver->init ? touch->driver->init(touch->driver->user) : 1U;
}

void EALGFX_TouchSetTransform(EALGFX_Touch *touch, uint8_t swap_xy,
                              uint8_t invert_x, uint8_t invert_y)
{
    if (!touch) return;
    touch->swap_xy = swap_xy ? 1U : 0U;
    touch->invert_x = invert_x ? 1U : 0U;
    touch->invert_y = invert_y ? 1U : 0U;
}

static void transform(EALGFX_Touch *touch, uint16_t *x, uint16_t *y)
{
    uint16_t tx = *x, ty = *y, limit_x = touch->width, limit_y = touch->height;
    if (touch->swap_xy) {
        uint16_t t = tx; tx = ty; ty = t;
        limit_x = touch->height; limit_y = touch->width;
    }
    if (tx >= limit_x) tx = (uint16_t)(limit_x - 1U);
    if (ty >= limit_y) ty = (uint16_t)(limit_y - 1U);
    if (touch->invert_x) tx = (uint16_t)(limit_x - 1U - tx);
    if (touch->invert_y) ty = (uint16_t)(limit_y - 1U - ty);
    *x = tx; *y = ty;
}

uint8_t EALGFX_TouchPoll(EALGFX_Touch *touch, EALGFX_TouchEvent *event)
{
    uint16_t x, y;
    uint8_t pressed;
    if (!touch || !touch->driver || !event) return 0U;
    if (!touch->driver->read(touch->driver->user, &x, &y, &pressed)) return 0U;
    transform(touch, &x, &y);
    if (pressed) {
        event->type = touch->was_pressed ? EALGFX_TOUCH_MOVE : EALGFX_TOUCH_DOWN;
        touch->last_x = x; touch->last_y = y; touch->was_pressed = 1U;
    } else {
        if (!touch->was_pressed) return 0U;
        event->type = EALGFX_TOUCH_UP;
        x = touch->last_x; y = touch->last_y; touch->was_pressed = 0U;
    }
    event->x = x; event->y = y;
    return 1U;
}
