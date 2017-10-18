
#include "Vector3f.h"

using antisocial::math::Vector3f;

Vector3f::Vector3f(float x, float y, float z)
    :   x(x),
        y(y),
        z(z)
{

}

Vector3f::~Vector3f()
{

}

float Vector3f::magnitude()
{
    return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3f::dot(const Vector3f& v)
{
    return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector3f& Vector3f::cross(const Vector3f& v)
{
    return Vector3f((y * v.z) - (z * v.y),
                    (z * v.x) - (x * v.z),
                    (x * v.y) - (y * v.x));
}

Vector3f& Vector3f::add(const Vector3f& v)
{
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f& Vector3f::subtract(const Vector3f& v)
{
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

float Vector3f::operator*(const Vector3f& v)
{
    return dot(v);
}

Vector3f& Vector3f::operator+(const Vector3f& v)
{
    return add(v);
}

Vector3f& Vector3f::operator-(const Vector3f& v)
{
    return subtract(v);
}
