#include "ealgfx_gfx2d.h"

static void display_fill(EALGFX_Surface *s,int x,int y,int w,int h,EALGFX_Color c)
{
    EALGFX_Display *d=(EALGFX_Display *)s->user;
    d->driver->fill_rect(d->driver->user,(uint16_t)x,(uint16_t)y,(uint16_t)w,(uint16_t)h,c);
}

void EALGFX_SurfaceFromDisplay(EALGFX_Surface *s,EALGFX_Display *d)
{
    if(!s||!d||!d->driver)return;
    s->width=(int16_t)d->driver->width;s->height=(int16_t)d->driver->height;
    s->fill_rect=display_fill;s->user=d;EALGFX_SurfaceResetClip(s);
}
void EALGFX_SurfaceSetClip(EALGFX_Surface *s,EALGFX_Rect r)
{
    int x0=r.x,y0=r.y,x1=r.x+r.w,y1=r.y+r.h;
    if(!s)return;
    if(x0<0)x0=0;
    if(y0<0)y0=0;
    if(x1>s->width)x1=s->width;
    if(y1>s->height)y1=s->height;
    if(x1<x0)x1=x0;
    if(y1<y0)y1=y0;
    s->clip.x=(int16_t)x0;s->clip.y=(int16_t)y0;s->clip.w=(int16_t)(x1-x0);s->clip.h=(int16_t)(y1-y0);
}
void EALGFX_SurfaceResetClip(EALGFX_Surface *s){EALGFX_Rect r;if(!s)return;r.x=0;r.y=0;r.w=s->width;r.h=s->height;EALGFX_SurfaceSetClip(s,r);}
void EALGFX_FillRect(EALGFX_Surface *s,int x,int y,int w,int h,EALGFX_Color c)
{
    int x1=x+w,y1=y+h,cx1,cy1;
    if(!s||!s->fill_rect||w<=0||h<=0)return;
    cx1=s->clip.x+s->clip.w;cy1=s->clip.y+s->clip.h;
    if(x<s->clip.x)x=s->clip.x;
    if(y<s->clip.y)y=s->clip.y;
    if(x1>cx1)x1=cx1;
    if(y1>cy1)y1=cy1;
    if(x1>x&&y1>y)s->fill_rect(s,x,y,x1-x,y1-y,c);
}
void EALGFX_Pixel(EALGFX_Surface *s,int x,int y,EALGFX_Color c){EALGFX_FillRect(s,x,y,1,1,c);}
void EALGFX_Clear(EALGFX_Surface *s,EALGFX_Color c){if(s)EALGFX_FillRect(s,0,0,s->width,s->height,c);}
void EALGFX_Rectangle(EALGFX_Surface *s,int x,int y,int w,int h,EALGFX_Color c){if(w<=0||h<=0)return;EALGFX_FillRect(s,x,y,w,1,c);EALGFX_FillRect(s,x,y+h-1,w,1,c);EALGFX_FillRect(s,x,y,1,h,c);EALGFX_FillRect(s,x+w-1,y,1,h,c);}
void EALGFX_Line(EALGFX_Surface *s,int x0,int y0,int x1,int y1,EALGFX_Color c)
{
    int dx=x1>x0?x1-x0:x0-x1,sx=x0<x1?1:-1,dy=y1>y0?y0-y1:y1-y0,sy=y0<y1?1:-1,err=dx+dy,e2;
    for(;;){EALGFX_Pixel(s,x0,y0,c);if(x0==x1&&y0==y1)break;e2=2*err;if(e2>=dy){err+=dy;x0+=sx;}if(e2<=dx){err+=dx;y0+=sy;}}
}
void EALGFX_Circle(EALGFX_Surface *s,int cx,int cy,int r,EALGFX_Color c)
{
    int x=0,y=r,d=1-r;if(r<0)return;while(x<=y){EALGFX_Pixel(s,cx+x,cy+y,c);EALGFX_Pixel(s,cx-x,cy+y,c);EALGFX_Pixel(s,cx+x,cy-y,c);EALGFX_Pixel(s,cx-x,cy-y,c);EALGFX_Pixel(s,cx+y,cy+x,c);EALGFX_Pixel(s,cx-y,cy+x,c);EALGFX_Pixel(s,cx+y,cy-x,c);EALGFX_Pixel(s,cx-y,cy-x,c);x++;if(d<0)d+=2*x+1;else{y--;d+=2*(x-y)+1;}}
}
void EALGFX_FillCircle(EALGFX_Surface *s,int cx,int cy,int r,EALGFX_Color c)
{
    int x=0,y=r,d=1-r;if(r<0)return;while(x<=y){EALGFX_FillRect(s,cx-x,cy+y,2*x+1,1,c);EALGFX_FillRect(s,cx-x,cy-y,2*x+1,1,c);EALGFX_FillRect(s,cx-y,cy+x,2*y+1,1,c);EALGFX_FillRect(s,cx-y,cy-x,2*y+1,1,c);x++;if(d<0)d+=2*x+1;else{y--;d+=2*(x-y)+1;}}
}
void EALGFX_Triangle(EALGFX_Surface *s,EALGFX_Point2i a,EALGFX_Point2i b,EALGFX_Point2i c,EALGFX_Color color){EALGFX_Line(s,a.x,a.y,b.x,b.y,color);EALGFX_Line(s,b.x,b.y,c.x,c.y,color);EALGFX_Line(s,c.x,c.y,a.x,a.y,color);}
