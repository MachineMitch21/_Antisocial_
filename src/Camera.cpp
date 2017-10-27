
#include "Camera.h"

#include <iostream>

using antisocial::graphics::Camera;
using namespace antisocial::input;

Camera::Camera(float fov, float x, float y, float z, float aspectRatio, float nearClip, float farClip)
    :   _fov(fov),
        _position(Vector3f(x, y, z)),
        _rotation(Vector3f(0.0f, 0.0f, 0.0f)),
        _front(Vector3f(0.0f, 0.0f, -1.0f)),
        _up(Vector3f(0.0f, 1.0f, 0.0f)),
        _worldUp(Vector3f(0.0f, 1.0f, 0.0f)),
        _aspectRatio(aspectRatio),
        _nearClip(nearClip),
        _farClip(farClip),
        _yaw(-90.0f),
        _pitch(0.0f),
        _movementSpeed(5.0f)
{

}

Camera::~Camera()
{

}

Matrix Camera::getViewMatrix()
{
    return Matrix::lookAt(_position, _position + _front, _up);
}

void Camera::setFOV(float fov)
{
    _fov = fov;
}

void Camera::setAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
}

void Camera::setNearClip(float nearClip)
{
    _nearClip = nearClip;
}

void Camera::setFarClip(float farClip)
{
    _farClip = farClip;
}

float Camera::getFOV()
{
    return _fov;
}

float Camera::getAspectRatio()
{
    return _aspectRatio;
}

float Camera::getNearClip()
{
    return _nearClip;
}

float Camera::getFarClip()
{
    return _farClip;
}

void Camera::move(Vector3f direction, float speedMultiplier, float xOffset, float yOffset, float deltaTime, bool constrain)
{
    float velocity = (_movementSpeed * speedMultiplier) * deltaTime;
    _position += direction * velocity;

    xOffset *= Input::LookSensitivity;
    yOffset *= Input::LookSensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    if (constrain)
    {
        if (_pitch > 89.0f)
        {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f)
        {
            _pitch = -89.0f;
        }
    }

    Vector3f front;

    front.x = cos(MathUtils::to_radians(_yaw)) * cos(MathUtils::to_radians(_pitch));
    front.y = sin(MathUtils::to_radians(_pitch));
    front.z = sin(MathUtils::to_radians(_yaw)) * cos(MathUtils::to_radians(_pitch));
    _front  = Vector3f::normalize(front);

    _right  = Vector3f::normalize(Vector3f::cross(_front, _worldUp));
    _up     = Vector3f::normalize(Vector3f::cross(_right, _front));
}
