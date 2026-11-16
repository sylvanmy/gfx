#include "ealgfx_gfx3d.h"

static const EALGFX_Vec3 cube_vertices[8]={
    {-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
    {-1,-1, 1},{1,-1, 1},{1,1, 1},{-1,1, 1}
};
static const EALGFX_Edge cube_edges[12]={
    {0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}
};
static const EALGFX_WireMesh cube={cube_vertices,8,cube_edges,12};
const EALGFX_WireMesh *EALGFX_BuiltinCube(void){return &cube;}

uint8_t EALGFX_ProjectPoint(EALGFX_Vec3 p,const EALGFX_Camera3D *c,EALGFX_Point2i *out)
{
    float z;if(!c||!out)return 0U;z=p.z+c->distance;if(z<=0.05f)return 0U;
    out->x=(int16_t)(c->center_x+p.x*c->focal_length/z);
    out->y=(int16_t)(c->center_y-p.y*c->focal_length/z);return 1U;
}
void EALGFX_DrawWireMesh(EALGFX_Surface *s,const EALGFX_WireMesh *mesh,const EALGFX_Camera3D *c,EALGFX_Color color)
{
    EALGFX_Mat4 rx,ry,rz,r;EALGFX_Point2i projected[32];uint8_t visible[32];uint16_t i;
    if(!s||!mesh||!c||mesh->vertex_count>32U)return;
    rx=EALGFX_Mat4RotationX(c->rotation_x);ry=EALGFX_Mat4RotationY(c->rotation_y);rz=EALGFX_Mat4RotationZ(c->rotation_z);
    r=EALGFX_Mat4Multiply(rz,EALGFX_Mat4Multiply(ry,rx));
    for(i=0;i<mesh->vertex_count;i++)visible[i]=EALGFX_ProjectPoint(EALGFX_Mat4TransformPoint(r,mesh->vertices[i]),c,&projected[i]);
    for(i=0;i<mesh->edge_count;i++){uint16_t a=mesh->edges[i].a,b=mesh->edges[i].b;if(a<mesh->vertex_count&&b<mesh->vertex_count&&visible[a]&&visible[b])EALGFX_Line(s,projected[a].x,projected[a].y,projected[b].x,projected[b].y,color);}
}
