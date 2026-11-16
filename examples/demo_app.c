#include "demo_app.h"
#include "ealgfx.h"
#include "ealgfx_port_stm32f407.h"

/* This file is application/test code. No LCD or Goodix register is used here. */
static EALGFX_Display display;
static EALGFX_Surface canvas;
static EALGFX_Touch touch;
static EALGFX_Camera3D camera;
static uint32_t previous_frame;
static int16_t last_touch_x, last_touch_y;

static void draw_2d_primitives(void)
{
    EALGFX_Point2i a={50,180},b={130,70},c={210,180};
    EALGFX_Rectangle(&canvas,30,30,210,180,EALGFX_WHITE);
    EALGFX_Line(&canvas,30,30,240,210,EALGFX_CYAN);
    EALGFX_Circle(&canvas,135,120,54,EALGFX_YELLOW);
    EALGFX_Triangle(&canvas,a,b,c,EALGFX_GREEN);
    EALGFX_FillCircle(&canvas,70,320,28,EALGFX_RED);
}

static void redraw_3d(void)
{
    /* Only the 3D viewport is cleared; the 2D test region remains unchanged. */
    EALGFX_FillRect(&canvas,280,20,500,380,(EALGFX_Color)0x0841U);
    EALGFX_Rectangle(&canvas,280,20,500,380,EALGFX_BLUE);
    EALGFX_DrawWireMesh(&canvas,EALGFX_BuiltinCube(),&camera,EALGFX_WHITE);
}

void DemoApp_Init(void)
{
    EALGFX_DisplayAttach(&display,&EALGFX_STM32F407_DisplayDriver);
    EALGFX_DisplayInit(&display);
    EALGFX_SurfaceFromDisplay(&canvas,&display);
    EALGFX_TouchAttach(&touch,&EALGFX_STM32F407_TouchDriver,canvas.width,canvas.height);
    EALGFX_TouchInit(&touch);
    EALGFX_Clear(&canvas,(EALGFX_Color)0x0841U);
    draw_2d_primitives();
    camera.rotation_x=0.35f;camera.rotation_y=0.35f;camera.rotation_z=0.0f;
    camera.distance=4.5f;camera.focal_length=310.0f;camera.center_x=530;camera.center_y=210;
    previous_frame=0U;last_touch_x=-1;last_touch_y=-1;redraw_3d();
}

void DemoApp_Update(uint32_t now_ms)
{
    EALGFX_TouchEvent e;
    if(EALGFX_TouchPoll(&touch,&e)){
        if(e.type==EALGFX_TOUCH_DOWN){last_touch_x=(int16_t)e.x;last_touch_y=(int16_t)e.y;}
        else if(e.type==EALGFX_TOUCH_MOVE&&last_touch_x>=0){
            camera.rotation_y+=(float)((int16_t)e.x-last_touch_x)*0.012f;
            camera.rotation_x+=(float)((int16_t)e.y-last_touch_y)*0.012f;
            last_touch_x=(int16_t)e.x;last_touch_y=(int16_t)e.y;redraw_3d();
        }else if(e.type==EALGFX_TOUCH_UP){last_touch_x=-1;last_touch_y=-1;}
    }
    if((uint32_t)(now_ms-previous_frame)>=33U){
        previous_frame=now_ms;
        if(last_touch_x<0){camera.rotation_y+=0.018f;camera.rotation_x+=0.007f;redraw_3d();}
    }
}
