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

GLfloat* Matrix::valueOf()
{
    // First Column
    _elements[0]   = xp.x;
    _elements[1]   = xp.y;
    _elements[2]   = xp.z;
    _elements[3]   = xp.w;

    // Second Column
    _elements[4]   = yp.x;
    _elements[5]   = yp.y;
    _elements[6]   = yp.z;
    _elements[7]   = yp.w;

    // Third Column
    _elements[8]   = zp.x;
    _elements[9]   = zp.y;
    _elements[10]  = zp.z;
    _elements[11]  = zp.w;

    // Fourth Column
    _elements[12]  = tp.x;
    _elements[13]  = tp.y;
    _elements[14]  = tp.z;
    _elements[15]  = tp.w;

    return _elements;
}

Matrix Matrix::perspective(float fov, float aspectRatio, float nearClip, float farClip)
{
    Matrix m = Matrix(1.0f);

    float t     = tan(to_radians(fov / 2));
    float f_n   = farClip - nearClip;

    m.xp.x = 1.0f / (aspectRatio * t);
    m.yp.y = 1.0f / t;
    m.zp.z = -(farClip + nearClip) / f_n;
    m.zp.w = -1.0f;
    m.tp.z = (-2.0f * farClip * nearClip) / f_n;
    m.tp.w = 0.0f;

    return m;
}

Matrix Matrix::orthographic(float left, float right, float bottom, float top, float nearClip, float farClip)
{
    Matrix m = Matrix(1.0f);

    float f_n = farClip - nearClip;

    m.xp.x = 2 / (right - left);
    m.yp.y = 2 / (top - bottom);
    m.zp.z = -2 / (f_n);
    m.tp.x = -(right + left) / (right - left);
    m.tp.y = -(top + bottom) / (top - bottom);
    m.tp.z = -(farClip + nearClip) / f_n;

    return m;
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

Matrix Matrix::operator*(const Matrix& m2)
{
    Matrix temp;
    // First Column
    temp.xp.x = xp.x * m2.xp.x + yp.x * m2.xp.y + zp.x * m2.xp.z + tp.x * m2.xp.w;
    temp.xp.y = xp.y * m2.xp.x + yp.y * m2.xp.y + zp.y * m2.xp.z + tp.y * m2.xp.w;
    temp.xp.z = xp.z * m2.xp.x + yp.z * m2.xp.y + zp.z * m2.xp.z + tp.z * m2.xp.w;
    temp.xp.w = xp.w * m2.xp.x + yp.w * m2.xp.y + zp.w * m2.xp.z + tp.w * m2.xp.w;

    // Second Column
    temp.yp.x = xp.x * m2.yp.x + yp.x * m2.yp.y + zp.x * m2.yp.z + tp.x * m2.yp.w;
    temp.yp.y = xp.y * m2.yp.x + yp.y * m2.yp.y + zp.y * m2.yp.z + tp.y * m2.yp.w;
    temp.yp.z = xp.z * m2.yp.x + yp.z * m2.yp.y + zp.z * m2.yp.z + tp.z * m2.yp.w;
    temp.yp.w = xp.w * m2.yp.x + yp.w * m2.yp.y + zp.w * m2.yp.z + tp.w * m2.yp.w;

    // Third Column
    temp.zp.x = xp.x * m2.zp.x + yp.x * m2.zp.y + zp.x * m2.zp.z + tp.x * m2.zp.w;
    temp.zp.y = xp.y * m2.zp.x + yp.y * m2.zp.y + zp.y * m2.zp.z + tp.y * m2.zp.w;
    temp.zp.z = xp.z * m2.zp.x + yp.z * m2.zp.y + zp.z * m2.zp.z + tp.z * m2.zp.w;
    temp.zp.w = xp.w * m2.zp.x + yp.w * m2.zp.y + zp.w * m2.zp.z + tp.w * m2.zp.w;

    // Fourth Column
    temp.tp.x = xp.x * m2.tp.x + yp.x * m2.tp.y + zp.x * m2.tp.z + tp.x * m2.tp.w;
    temp.tp.y = xp.y * m2.tp.x + yp.y * m2.tp.y + zp.y * m2.tp.z + tp.y * m2.tp.w;
    temp.tp.z = xp.z * m2.tp.x + yp.z * m2.tp.y + zp.z * m2.tp.z + tp.z * m2.tp.w;
    temp.tp.w = xp.w * m2.tp.x + yp.w * m2.tp.y + zp.w * m2.tp.z + tp.w * m2.tp.w;

    return temp;
}

Matrix& Matrix::operator*=(const Matrix& m2)
{
    *this = *this * m2;

    return *this;
}

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
    return (this->xp == m2.xp && this->yp == m2.yp && this->zp == m2.zp && this->tp == m2.tp);
}
