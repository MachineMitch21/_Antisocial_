
#include "Time.h"

using antisocial::Time;

float Time::_elapsedTime = 0.0f;
float Time::_deltaTime = 0.0f;
float Time::_lastFrame = 0.0f;

float Time::ElapsedTime()
{
    return _elapsedTime;
}

float Time::DeltaTime()
{
    return _deltaTime;
}

float Time::LastFrame()
{
    return _lastFrame;
}
