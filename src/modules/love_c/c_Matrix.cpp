// STD
#include <cstring> // memcpy

#include "c_Matrix.h"

#include "runtime_c.h"

#include "common/Matrix.h"

using namespace love;


void love_Matrix4_setIdentity(LoveC_Matrix4* mat) {
  unwrap<Matrix4>(mat)->setIdentity();
}

void love_Matrix4_setTranslation(LoveC_Matrix4* mat, float x, float y) {
  unwrap<Matrix4>(mat)->setTranslation(x, y);
}

void love_Matrix4_setRotation(LoveC_Matrix4* mat, float rad) {
  unwrap<Matrix4>(mat)->setRotation(rad);
}

void love_Matrix4_setScale(LoveC_Matrix4* mat, float sx, float sy) {
  unwrap<Matrix4>(mat)->setScale(sx, sy);
}

void love_Matrix4_setShear(LoveC_Matrix4* mat, float kx, float ky) {
  unwrap<Matrix4>(mat)->setShear(kx, ky);
}

void love_Matrix4_getApproximateScale(const LoveC_Matrix4* mat, float* outSx, float* outSy) {
  float sx, sy;
  unwrap<const Matrix4>(mat)->getApproximateScale(sx, sy);
  *outSx = sx;
  *outSy = sy;
}

void love_Matrix4_setRawTransformation(LoveC_Matrix4* mat, float t00, float t10, float t01, float t11, float x, float y) {
  unwrap<Matrix4>(mat)->setRawTransformation(t00, t10, t01, t11, x, y);
}

void love_Matrix4_setTransformation(LoveC_Matrix4* mat, float x, float y, float angle, float sx, float sy, float ox, float oy, float kx, float ky) {
  unwrap<Matrix4>(mat)->setTransformation(x, y, angle, sx, sy, ox, oy, kx, ky);
}

void love_Matrix4_translate(LoveC_Matrix4* mat, float x, float y) {
  unwrap<Matrix4>(mat)->translate(x, y);
}

void love_Matrix4_rotate(LoveC_Matrix4* mat, float rad) {
  unwrap<Matrix4>(mat)->rotate(rad);
}

void love_Matrix4_scale(LoveC_Matrix4* mat, float sx, float sy) {
  unwrap<Matrix4>(mat)->scale(sx, sy);
}

void love_Matrix4_shear(LoveC_Matrix4* mat, float kx, float ky) {
  unwrap<Matrix4>(mat)->shear(kx, ky);
}

LoveC_Bool love_Matrix4_isAffine2DTransform(const LoveC_Matrix4* mat) {
  return unwrap<const Matrix4>(mat)->isAffine2DTransform();
}

void love_Matrix4_inverse(const LoveC_Matrix4* mat, LoveC_Matrix4* outMatInverse) {
  auto outMatInverse_ = unwrap<Matrix4>(outMatInverse);

  Matrix4 inv = unwrap<const Matrix4>(mat)->inverse();
  memcpy(outMatInverse_, inv.getElements(), sizeof(float) * 16);
}

void love_Matrix4_ortho(const LoveC_Matrix4* mat, float left, float right, float bottom, float top, float near, float far, LoveC_Matrix4* outMatOrtho) {
  auto outMatOrtho_ = unwrap<Matrix4>(outMatOrtho);

  Matrix4 ortho = unwrap<const Matrix4>(mat)->inverse();
  memcpy(outMatOrtho_, ortho.getElements(), sizeof(float) * 16);
}
