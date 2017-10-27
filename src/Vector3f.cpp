
#include "Vector3f.h"

using antisocial::math::Vector3f;

Vector3f::Vector3f()
    :   x(0.0f),
        y(0.0f),
        z(0.0f)
{

}

Vector3f::Vector3f(float x, float y, float z)
    :   x(x),
        y(y),
        z(z)
{

}

Vector3f::~Vector3f()
{

}

Vector3f Vector3f::normalize(const Vector3f& v)
{

    Vector3f newV = v;
    float n = newV.magnitude();

    n = sqrt(n);

    n = 1.0f / n;

    newV.x *= n;
    newV.y *= n;
    newV.z *= n;

    return newV;
}

Vector3f Vector3f::cross(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f((v1.y * v2.z) - (v1.z * v2.y),
                    (v1.z * v2.x) - (v1.x * v2.z),
                    (v1.x * v2.y) - (v1.y * v2.x));
}

float Vector3f::magnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

float Vector3f::dot(const Vector3f& v1, const Vector3f& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


Vector3f Vector3f::add(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3f Vector3f::subtract(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3f Vector3f::scale(float scalar)
{
    return Vector3f(x * scalar, y * scalar, z * scalar);
}

Vector3f Vector3f::Lerp(Vector3f v1, Vector3f v2, float t)
{
    return v1 * t + v2 * (1.0f - t);
}

Vector3f Vector3f::operator*(float scalar)
{
    return scale(scalar);
}

Vector3f& Vector3f::operator+=(const Vector3f& v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

Vector3f Vector3f::operator-()
{
    return Vector3f(-x, -y, -z);
}

Vector3f antisocial::math::operator+(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f::add(v1, v2);
}


Vector3f antisocial::math::operator-(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f::subtract(v1, v2);
}
