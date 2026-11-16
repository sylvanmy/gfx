#include "ealgfx_port_stm32f407.h"
#include "lcd_reg.h"
#include "touch_reg.h"

static void lcd_init(void *user){(void)user;LCD_Init();}
static void lcd_fill(void *user,uint16_t x,uint16_t y,uint16_t w,uint16_t h,EALGFX_Color c){(void)user;LCD_FillRect(x,y,w,h,c);}
static void lcd_blit(void *user,uint16_t x,uint16_t y,uint16_t w,uint16_t h,const EALGFX_Color *p){(void)user;LCD_BlitRGB565(x,y,w,h,p);}
const EALGFX_DisplayDriver EALGFX_STM32F407_DisplayDriver={LCD_WIDTH,LCD_HEIGHT,lcd_init,lcd_fill,lcd_blit,0};

static uint8_t touch_init(void *user){(void)user;return Touch_Init();}
static uint8_t touch_read(void *user,uint16_t *x,uint16_t *y,uint8_t *pressed)
{
    TouchPoint p;(void)user;if(!Touch_Poll(&p))return 0U;*x=p.x;*y=p.y;*pressed=p.pressed;return 1U;
}
const EALGFX_TouchDriver EALGFX_STM32F407_TouchDriver={touch_init,touch_read,0};
