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
