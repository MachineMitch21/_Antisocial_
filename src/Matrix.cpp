#include "Matrix.h"
#include <iostream>

namespace antisocial
{
    namespace math
    {
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
            :   xp(col1),
                yp(col2),
                zp(col3),
                tp(col4)
        {

        }

        Matrix::Matrix( float Xx, float Xy, float Xz, float Xo,
                        float Yx, float Yy, float Yz, float Yo,
                        float Zx, float Zy, float Zz, float Zo,
                        float Tx, float Ty, float Tz, float To)
                    :   xp(Xx, Xy, Xz, Xo),
                        yp(Yx, Yy, Yz, Yo),
                        zp(Zx, Zy, Zz, Zo),
                        tp(Tx, Ty, Tz, To)
        {

        }

        Matrix::Matrix(float matVars[16])
            :   xp(matVars[0], matVars[1], matVars[2], matVars[3]),
                yp(matVars[4], matVars[5], matVars[6], matVars[7]),
                zp(matVars[8], matVars[9], matVars[10], matVars[11]),
                tp(matVars[12], matVars[13], matVars[14], matVars[15])
        {

        }

        Matrix::~Matrix()
        {

        }

        float* Matrix::valueOf()
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
            Matrix m(1.0f);

            float t     = tan(MathUtils::to_radians(fov / 2));
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
            Matrix m(1.0f);

            float f_n = farClip - nearClip;

            m.xp.x = 2 / (right - left);
            m.yp.y = 2 / (top - bottom);
            m.zp.z = -2 / (f_n);
            m.tp.x = -(right + left) / (right - left);
            m.tp.y = -(top + bottom) / (top - bottom);
            m.tp.z = -(farClip + nearClip) / f_n;

            return m;
        }

        Matrix Matrix::lookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
        {
            Vector3f zDir = eye - target;
            Vector3f zAxis = Vector3f::normalize(zDir);
            Vector3f xAxis = Vector3f::normalize(Vector3f::cross(up, zAxis));
            Vector3f yAxis = Vector3f::normalize(Vector3f::cross(zAxis, xAxis));

            Matrix lookAt = {
                Vector4f( xAxis.x,                    yAxis.x,                    zAxis.x,                    0.0f ),
                Vector4f( xAxis.y,                    yAxis.y,                    zAxis.y,                    0.0f ),
                Vector4f( xAxis.z,                    yAxis.z,                    zAxis.z,                    0.0f ),
                Vector4f( -Vector3f::dot(xAxis, eye), -Vector3f::dot(yAxis, eye), -Vector3f::dot(zAxis, eye), 1.0f )
            };

            return lookAt;
        }

        Matrix Matrix::translate(Matrix& m, const Vector3f& v1)
        {
            m.tp.x += v1.x;
            m.tp.y += v1.y;
            m.tp.z += v1.z;

            return m;
        }

        Matrix Matrix::scale(Matrix& m, const Vector3f& v1)
        {
            m = Matrix(1.0f);

            m.xp.x = v1.x;
            m.yp.y = v1.y;
            m.zp.z = v1.z;

            return m;
        }

        Matrix Matrix::rotate(Matrix& m, const Vector3f& v1, float angle)
        {
            m = Matrix(1.0f);

            float x = v1.x;
            float y = v1.y;
            float z = v1.z;

            float c = cos(angle);
            float s = sin(angle);
            float t = 1.0f - c;

            float tx    = t * x;
            float ty    = t * y;
            float tz    = t * z;
            float txy   = tx * y;
            float txz   = tx * z;
            float tyz   = ty * z;
            float sx    = s * x;
            float sy    = s * y;
            float sz    = s * z;

            m.xp.x = c + tx * x;
            m.xp.y = txy + sz;
            m.xp.z = txz - sy;
            m.xp.w = 0.0f;

            m.yp.x = txy - sz;
            m.yp.y = c + ty * y;
            m.yp.z = tyz + sx;
            m.yp.w = 0.0f;

            m.zp.x = txz + sy;
            m.zp.y = tyz - sx;
            m.zp.z = c + tz * z;
            m.zp.w = 0.0f;

            m.tp.x = 0.0f;
            m.tp.y = 0.0f;
            m.tp.z = 0.0f;
            m.tp.w = 1.0f;

            return m;
        }

        Matrix& Matrix::multiply(const Matrix& m2)
        {
            Matrix temp(1.0f);
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

            *this = temp;
            return *this;
        }

        //Operator overloads
        Matrix operator*(Matrix m1, const Matrix& m2)
        {
            return m1.multiply(m2);
        }

        Matrix& Matrix::operator*=(const Matrix& m2)
        {
            return multiply(m2);
        }

        Matrix Matrix::operator+(const Matrix& m2)
        {
            Matrix temp(1.0f);
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
    }
}
