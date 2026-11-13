#include "halvorson.hpp"

Vec3 Halvorson::derivative(const Vec3 &currentPosition) const
{
    float dx = -a * currentPosition.x - 4.0f * currentPosition.y - 4.0f * currentPosition.z - powf(currentPosition.y, 2.0f);
    float dy = -a * currentPosition.y - 4.0f * currentPosition.z - 4.0f * currentPosition.x - powf(currentPosition.z, 2.0f);
    float dz = -a * currentPosition.z - 4.0f * currentPosition.x - 4.0f * currentPosition.y - powf(currentPosition.x, 2.0f);

    return Vec3(dx, dy, dz);
}

Vec3 Halvorson::initialState() const
{
    return Vec3(0.0, 0.0, 0.0);
}

Vec3 Halvorson::getCameraPosition() const
{
    return Vec3(5.0, 5.0, 5.0);
}

Vec3 Halvorson::getCameraTarget() const
{
    return Vec3(0.0, 0.0, 0.0);
}

float Halvorson::getParticleSize() const
{
    return 0.1;
}