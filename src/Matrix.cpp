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

Matrix::Matrix(float d)
:   xp(d,    0.0f, 0.0f, 0.0f),
    yp(0.0f, d,    0.0f, 0.0f),
    zp(0.0f, 0.0f, d,    0.0f),
    tp(0.0f, 0.0f, 0.0f, d   )
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

Matrix::Matrix(float matVars[16])
            : xp(matVars[0], matVars[1], matVars[2], matVars[3]),
              yp(matVars[4], matVars[5], matVars[6], matVars[7]),
              zp(matVars[8], matVars[9], matVars[10], matVars[11]),
              tp(matVars[12], matVars[13], matVars[14], matVars[15])
{

}

Matrix::~Matrix()
{

}

void Matrix::translate(const Vector3f& v1)
{
    tp.x += (v1.x * xp.x) + (v1.y * yp.x) + (v1.z * zp.x);
    tp.y += (v1.x * xp.y) + (v1.y * yp.y) + (v1.z * zp.y);
    tp.z += (v1.x * xp.z) + (v1.y * yp.z) + (v1.z * zp.z);
    tp.w += (v1.x * xp.w) + (v1.y * yp.w) + (v1.z * zp.w);
}

void Matrix::scale(const Vector3f& v1)
{
    xp.x = v1.x;
    yp.y = v1.y;
    zp.z = v1.z;
}

void Matrix::rotate(const Vector3f& v1, float angle)
{
    float x = v1.x;
    float y = v1.y;
    float z = v1.z;

    float c = cos(angle);
    float s = sin(angle);
    float t = 1.0f - c;

    float tx    = t * x;
    float ty    = t * y;
    float tz    = t * z;
    float txs   = tx * tx;
    float tys   = ty * ty;
    float tzs   = tz * tz;
    float txy   = tx * y;
    float txz   = tx * z;
    float tyz   = ty * z;
    float sx    = s * x;
    float sy    = s * y;
    float sz    = s * z;

    xp.x = txs + c;
    xp.y = txy + sz;
    xp.z = txz + sy;

    yp.x = txy - sz;
    yp.y = tys + c;
    yp.z = tyz + sx;

    zp.x = txz + sy;
    zp.y = tyz - sx;
    zp.z = tzs + c;
}

//Operator overloads

Matrix Matrix::operator+(const Matrix& m2)
{
    Matrix temp;
    temp.xp = this->xp + m2.xp;
    temp.yp = this->yp + m2.yp;
    temp.zp = this->zp + m2.zp;
    temp.tp = this->tp + m2.tp;


    return temp;
}

Matrix& Matrix::operator+=(const Matrix& m2)
{
    this->xp += m2.xp;
    this->yp += m2.yp;
    this->zp += m2.zp;
    this->tp += m2.tp;

    return *this;
}

bool Matrix::operator==(const Matrix& m2)
{
    if(this->xp == m2.xp && this->yp == m2.yp && this->zp == m2.zp && this->tp == m2.tp)
    {
        return true;
    }else{
        return false;
    }
}
