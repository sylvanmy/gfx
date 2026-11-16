#include "ealgfx_display.h"

uint8_t EALGFX_DisplayAttach(EALGFX_Display *display,
                             const EALGFX_DisplayDriver *driver)
{
    if (!display || !driver || !driver->fill_rect || !driver->width || !driver->height)
        return 0U;
    display->driver = driver;
    return 1U;
}

void EALGFX_DisplayInit(EALGFX_Display *display)
{
    if (display && display->driver && display->driver->init)
        display->driver->init(display->driver->user);
}

void EALGFX_DisplayClear(EALGFX_Display *display, EALGFX_Color color)
{
    if (display && display->driver)
        display->driver->fill_rect(display->driver->user, 0U, 0U,
                                  display->driver->width,
                                  display->driver->height, color);
}
