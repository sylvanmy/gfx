#include "ealgfx.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define W 96
#define H 64
static EALGFX_Color framebuffer[W*H];
static unsigned touch_step;

static void host_fill(void *u,uint16_t x,uint16_t y,uint16_t w,uint16_t h,EALGFX_Color c)
{uint16_t xx,yy;(void)u;for(yy=y;yy<y+h;yy++)for(xx=x;xx<x+w;xx++)framebuffer[yy*W+xx]=c;}
static uint8_t host_touch(void *u,uint16_t *x,uint16_t *y,uint8_t *pressed)
{(void)u;if(touch_step==0){*x=10;*y=20;*pressed=1;}else if(touch_step==1){*x=12;*y=24;*pressed=1;}else if(touch_step==2){*x=12;*y=24;*pressed=0;}else return 0;touch_step++;return 1;}

int main(void)
{
    const EALGFX_DisplayDriver dd={W,H,0,host_fill,0,0};
    const EALGFX_TouchDriver td={0,host_touch,0};
    EALGFX_Display d;EALGFX_Surface s;EALGFX_Touch t;EALGFX_TouchEvent e;
    EALGFX_Vec3 v={3,0,4},n=EALGFX_Vec3Normalize(v);EALGFX_Mat4 r;
    assert(EALGFX_DisplayAttach(&d,&dd));EALGFX_SurfaceFromDisplay(&s,&d);
    EALGFX_Clear(&s,EALGFX_BLACK);EALGFX_Rectangle(&s,2,2,20,12,EALGFX_WHITE);
    EALGFX_Line(&s,0,0,30,30,EALGFX_RED);EALGFX_FillCircle(&s,50,30,8,EALGFX_GREEN);
    assert(framebuffer[0]==EALGFX_RED);assert(framebuffer[30*W+50]==EALGFX_GREEN);
    assert(fabsf(EALGFX_Vec3Length(n)-1.0f)<0.0001f);
    r=EALGFX_Mat4RotationZ(EALGFX_PI*0.5f);v.x=1;v.y=0;v.z=0;v=EALGFX_Mat4TransformPoint(r,v);
    assert(fabsf(v.x)<0.0001f&&fabsf(v.y-1.0f)<0.0001f);
    assert(EALGFX_TouchAttach(&t,&td,W,H));assert(EALGFX_TouchPoll(&t,&e)&&e.type==EALGFX_TOUCH_DOWN);
    assert(EALGFX_TouchPoll(&t,&e)&&e.type==EALGFX_TOUCH_MOVE);assert(EALGFX_TouchPoll(&t,&e)&&e.type==EALGFX_TOUCH_UP);
    puts("EAL-GFX core tests: PASS");return 0;
}
