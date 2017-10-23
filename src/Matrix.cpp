#include "Matrix.h"
#include <iostream>

using antisocial::math::Matrix;
using antisocial::math::Vector4f;

Matrix::Matrix()
    :   xp(0.0f, 0.0f, 0.0f, 0.0f),
        yp(0.0f, 0.0f, 0.0f, 0.0f),
        zp(0.0f, 0.0f, 0.0f, 0.0f),
        tp(0.0f, 0.0f, 0.0f, 0.0f)
{

}

Matrix::Matrix(Vector4f col1, Vector4f col2, Vector4f col3, Vector4f col4)
    : xp(col1),
      yp(col2),
      zp(col3),
      tp(col4)
{

}

Matrix::Matrix( float Xx, float Xy, float Xz, float Xo,
                float Yx, float Yy, float Yz, float Yo,
                float Zx, float Zy, float Zz, float Zo,
                float Tx, float Ty, float Tz, float To)
                : xp(Xx, Xy, Xz, Xo),
                  yp(Yx, Yy, Yz, Yo),
                  zp(Zx, Zy, Zz, Zo),
                  tp(Tx, Ty, Tz, To)
{

}
