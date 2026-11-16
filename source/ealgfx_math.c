#include "ealgfx_math.h"
#include <math.h>

float EALGFX_DegToRad(float d) { return d * (EALGFX_PI / 180.0f); }
float EALGFX_ClampF(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
EALGFX_Vec3 EALGFX_Vec3Add(EALGFX_Vec3 a,EALGFX_Vec3 b){EALGFX_Vec3 r={a.x+b.x,a.y+b.y,a.z+b.z};return r;}
EALGFX_Vec3 EALGFX_Vec3Sub(EALGFX_Vec3 a,EALGFX_Vec3 b){EALGFX_Vec3 r={a.x-b.x,a.y-b.y,a.z-b.z};return r;}
EALGFX_Vec3 EALGFX_Vec3Scale(EALGFX_Vec3 v,float s){EALGFX_Vec3 r={v.x*s,v.y*s,v.z*s};return r;}
float EALGFX_Vec3Dot(EALGFX_Vec3 a,EALGFX_Vec3 b){return a.x*b.x+a.y*b.y+a.z*b.z;}
EALGFX_Vec3 EALGFX_Vec3Cross(EALGFX_Vec3 a,EALGFX_Vec3 b){EALGFX_Vec3 r={a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};return r;}
float EALGFX_Vec3Length(EALGFX_Vec3 v){return sqrtf(EALGFX_Vec3Dot(v,v));}
EALGFX_Vec3 EALGFX_Vec3Normalize(EALGFX_Vec3 v){float n=EALGFX_Vec3Length(v);return n>0.000001f?EALGFX_Vec3Scale(v,1.0f/n):v;}

EALGFX_Mat4 EALGFX_Mat4Identity(void)
{
    EALGFX_Mat4 r={{{0}}}; int i; for(i=0;i<4;i++)r.m[i][i]=1.0f; return r;
}
EALGFX_Mat4 EALGFX_Mat4Multiply(EALGFX_Mat4 a,EALGFX_Mat4 b)
{
    EALGFX_Mat4 r={{{0}}}; int row,col,k;
    for(row=0;row<4;row++)for(col=0;col<4;col++)
        for(k=0;k<4;k++)r.m[row][col]+=a.m[row][k]*b.m[k][col];
    return r;
}
EALGFX_Mat4 EALGFX_Mat4Translation(float x,float y,float z){EALGFX_Mat4 r=EALGFX_Mat4Identity();r.m[0][3]=x;r.m[1][3]=y;r.m[2][3]=z;return r;}
EALGFX_Mat4 EALGFX_Mat4Scale(float x,float y,float z){EALGFX_Mat4 r=EALGFX_Mat4Identity();r.m[0][0]=x;r.m[1][1]=y;r.m[2][2]=z;return r;}
EALGFX_Mat4 EALGFX_Mat4RotationX(float a){EALGFX_Mat4 r=EALGFX_Mat4Identity();float c=cosf(a),s=sinf(a);r.m[1][1]=c;r.m[1][2]=-s;r.m[2][1]=s;r.m[2][2]=c;return r;}
EALGFX_Mat4 EALGFX_Mat4RotationY(float a){EALGFX_Mat4 r=EALGFX_Mat4Identity();float c=cosf(a),s=sinf(a);r.m[0][0]=c;r.m[0][2]=s;r.m[2][0]=-s;r.m[2][2]=c;return r;}
EALGFX_Mat4 EALGFX_Mat4RotationZ(float a){EALGFX_Mat4 r=EALGFX_Mat4Identity();float c=cosf(a),s=sinf(a);r.m[0][0]=c;r.m[0][1]=-s;r.m[1][0]=s;r.m[1][1]=c;return r;}
EALGFX_Vec3 EALGFX_Mat4TransformPoint(EALGFX_Mat4 m,EALGFX_Vec3 p)
{
    EALGFX_Vec3 r;
    r.x=m.m[0][0]*p.x+m.m[0][1]*p.y+m.m[0][2]*p.z+m.m[0][3];
    r.y=m.m[1][0]*p.x+m.m[1][1]*p.y+m.m[1][2]*p.z+m.m[1][3];
    r.z=m.m[2][0]*p.x+m.m[2][1]*p.y+m.m[2][2]*p.z+m.m[2][3];
    return r;
}
