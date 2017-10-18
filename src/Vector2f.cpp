
#include "Vector2f.h"

using antisocial::math::Vector2f;

Vector2f::Vector2f(float x, float y)
    :   x(x),
        y(y)
{

}

Vector2f::~Vector2f()
{

}

float Vector2f::magnitude()
{
    return sqrt((x * x) + (y * y));
}

float Vector2f::dot(const Vector2f& v)
{
    return (x * v.x) + (y * v.y);
}

Vector2f Vector2f::add(const Vector2f& v)
{
    return Vector2f(x + v.x, y + v.y);
}

Vector2f Vector2f::subtract(const Vector2f& v)
{
    return Vector2f(x - v.x, y - v.y);
}

float Vector2f::operator*(const Vector2f& v)
{
    return dot(v);
}

Vector2f Vector2f::operator+(const Vector2f& v)
{
    return add(v);
}

Vector2f Vector2f::operator-(const Vector2f& v)
{
    return subtract(v);
}
