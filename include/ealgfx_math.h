#ifndef EALGFX_MATH_H
#define EALGFX_MATH_H

#include "ealgfx_types.h"

#define EALGFX_PI 3.14159265358979323846f

float EALGFX_DegToRad(float degrees);
float EALGFX_ClampF(float value, float low, float high);
EALGFX_Vec3 EALGFX_Vec3Add(EALGFX_Vec3 a, EALGFX_Vec3 b);
EALGFX_Vec3 EALGFX_Vec3Sub(EALGFX_Vec3 a, EALGFX_Vec3 b);
EALGFX_Vec3 EALGFX_Vec3Scale(EALGFX_Vec3 v, float scale);
float EALGFX_Vec3Dot(EALGFX_Vec3 a, EALGFX_Vec3 b);
EALGFX_Vec3 EALGFX_Vec3Cross(EALGFX_Vec3 a, EALGFX_Vec3 b);
float EALGFX_Vec3Length(EALGFX_Vec3 v);
EALGFX_Vec3 EALGFX_Vec3Normalize(EALGFX_Vec3 v);
EALGFX_Mat4 EALGFX_Mat4Identity(void);
EALGFX_Mat4 EALGFX_Mat4Multiply(EALGFX_Mat4 a, EALGFX_Mat4 b);
EALGFX_Mat4 EALGFX_Mat4Translation(float x, float y, float z);
EALGFX_Mat4 EALGFX_Mat4Scale(float x, float y, float z);
EALGFX_Mat4 EALGFX_Mat4RotationX(float radians);
EALGFX_Mat4 EALGFX_Mat4RotationY(float radians);
EALGFX_Mat4 EALGFX_Mat4RotationZ(float radians);
EALGFX_Vec3 EALGFX_Mat4TransformPoint(EALGFX_Mat4 m, EALGFX_Vec3 p);

#endif
