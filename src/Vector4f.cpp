
#include "Vector4f.h"

using antisocial::math::Vector4f;

Vector4f::Vector4f(float x, float y, float z, float w)
    :   x(x),
        y(y),
        z(z),
        w(w)
{

}

Vector4f::~Vector4f()
{

}

float Vector4f::magnitude()
{
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4f::dot(const Vector4f& v)
{
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

Vector4f Vector4f::add(const Vector4f& v)
{
    return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4f Vector4f::subtract(const Vector4f& v)
{
    return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
}

float Vector4f::operator*(const Vector4f& v)
{
    return dot(v);
}

Vector4f Vector4f::operator+(const Vector4f& v)
{
    return add(v);
}

Vector4f Vector4f::operator-(const Vector4f& v)
{
    return subtract(v);
}

Vector4f& Vector4f::operator+=(const Vector4f& v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;
    return *this;
}

bool Vector4f::operator==(const Vector4f& v)
{
    if(this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w)
    {
        return true;
    }else{
        return false;
    }
}
