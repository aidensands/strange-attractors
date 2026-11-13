#include "lorenz.hpp"


Vec3 Lorenz::initialState() const
{
    return Vec3(1.0,1.0,1.0);
}

Vec3 Lorenz::derivative(const Vec3 &currentPosition) const
{
    // Returns the derivitave of the Lorenz system given the current position

    float dx = sigma * (currentPosition.y - currentPosition.x);
    float dy = currentPosition.x * (rho - currentPosition.z) - currentPosition.y;
    float dz = currentPosition.x * currentPosition.y - beta * currentPosition.z;

    return Vec3(dx, dy, dz);
}

Vec3 Lorenz::getCameraPosition() const
{
    return Vec3(10.0, 10.0, 25.0);
}

Vec3 Lorenz::getCameraTarget() const
{
    return Vec3(0.0, 0.0, 10.0);
}

float Lorenz::getParticleSize() const
{
    return 0.20f;
}