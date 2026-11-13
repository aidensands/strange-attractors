#include "vec3.hpp"
#include "aizawa.hpp"
#include <cmath>


Vec3 Aizawa::initialState() const
{
    return Vec3(0.1, 0.0, 0.0);
}

Vec3 Aizawa::derivative(const Vec3 &currentPosition) const
{
    float dx = (currentPosition.z - b) * currentPosition.x - d * currentPosition.y;
    float dy = d * currentPosition.x + (currentPosition.z - b) * currentPosition.y;
    float dz = c + a * currentPosition.z - (powf(currentPosition.z, 3.0f) / 3) - (powf(currentPosition.x, 2.0f) + powf(currentPosition.y, 2.0f)) * (1 + e * currentPosition.z) + f * currentPosition.z * powf(currentPosition.x, 3.0);
    return Vec3(dx, dy, dz);
}

Vec3 Aizawa::getCameraPosition() const
{
    return Vec3(1.0, 1.0, 1.0);
}

Vec3 Aizawa::getCameraTarget() const
{
    return Vec3(0.0, 0.0, 0.0);
}


float Aizawa::getParticleSize() const
{
    return 0.05;
}