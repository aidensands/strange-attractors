#include "sprott-linz.hpp"

// FIXME: Something in the Sprott-Linz system is causing particles to run away;

Vec3 SprottLinz::derivative(const Vec3 &currentPosition) const
{
    float dx = currentPosition.y + currentPosition.z;
    float dy = -currentPosition.x + a * currentPosition.y;
    float dz = powf(currentPosition.x, 2.0f) - currentPosition.z;
    
    return Vec3(dx, dy, dz);
}

Vec3 SprottLinz::initialState() const
{
    return Vec3(0.0, 0.0, 0.0);
}

Vec3 SprottLinz::getCameraPosition() const
{
    return Vec3(5.0, 5.0, 5.0);
}

Vec3 SprottLinz::getCameraTarget() const
{
    return Vec3(0.0, 0.0, 0.0);
}

float SprottLinz::getParticleSize() const
{
    return 0.05;
}