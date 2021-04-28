#ifndef LOVE_C_MATRIX_H
#define LOVE_C_MATRIX_H

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN


typedef struct LoveC_Matrix4
{
  float elements[16];
} LoveC_Matrix4;

LOVE_EXPORT void love_Matrix4_setIdentity(LoveC_Matrix4* mat);
LOVE_EXPORT void love_Matrix4_setTranslation(LoveC_Matrix4* mat, float x, float y);
LOVE_EXPORT void love_Matrix4_setRotation(LoveC_Matrix4* mat, float rad);
LOVE_EXPORT void love_Matrix4_setScale(LoveC_Matrix4* mat, float sx, float sy);
LOVE_EXPORT void love_Matrix4_setShear(LoveC_Matrix4* mat, float kx, float ky);
LOVE_EXPORT void love_Matrix4_getApproximateScale(const LoveC_Matrix4* mat, float* outSx, float* outSy);
LOVE_EXPORT void love_Matrix4_setRawTransformation(LoveC_Matrix4* mat, float t00, float t10, float t01, float t11, float x, float y);
LOVE_EXPORT void love_Matrix4_setTransformation(LoveC_Matrix4* mat, float x, float y, float angle, float sx, float sy, float ox, float oy, float kx, float ky);
LOVE_EXPORT void love_Matrix4_translate(LoveC_Matrix4* mat, float x, float y);
LOVE_EXPORT void love_Matrix4_rotate(LoveC_Matrix4* mat, float rad);
LOVE_EXPORT void love_Matrix4_scale(LoveC_Matrix4* mat, float sx, float sy);
LOVE_EXPORT void love_Matrix4_shear(LoveC_Matrix4* mat, float kx, float ky);
LOVE_EXPORT LoveC_Bool love_Matrix4_isAffine2DTransform(const LoveC_Matrix4* mat);
LOVE_EXPORT void love_Matrix4_inverse(const LoveC_Matrix4* mat, LoveC_Matrix4* outMatInverse);
LOVE_EXPORT void love_Matrix4_ortho(const LoveC_Matrix4* mat, float left, float right, float bottom, float top, float near, float far, LoveC_Matrix4* outMatOrtho);


LOVE_C_EXTERN_C_END

#endif // LOVE_C_MATRIX_H
