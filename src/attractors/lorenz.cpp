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