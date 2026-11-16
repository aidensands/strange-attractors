#include "vec3.hpp"
#include "arneodo.hpp"
#include <cmath>

Vec3 Arneodo::initialState() const
{
    return Vec3(1.0, 1.0, 0.0);
}

Vec3 Arneodo::derivative(const Vec3 &currentPosition) const
{
    float dx = currentPosition.y;
    float dy = currentPosition.z;
    float dz = -a*currentPosition.x - b*currentPosition.y - currentPosition.z - c * powf(currentPosition.x, 3.0f);
    return Vec3(dx, dy, dz);
}

Vec3 Arneodo::getCameraPosition() const
{
    return Vec3(20.0,20.0,20.0);
}

Vec3 Arneodo::getCameraTarget() const 
{
    return Vec3(0.0,0.0,0.0);
}

float Arneodo::getParticleSize() const
{
    return 0.15;
}