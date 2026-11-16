#include "vec3.hpp"
#include "chenlee.hpp"
#include <cmath>

Vec3 Chenlee::initialState() const
{
 return Vec3(0.2, 0.2, 0.2);
}

Vec3 Chenlee::derivative(const Vec3 &currentPosition) const
{
    float dx = a*currentPosition.x - currentPosition.y*currentPosition.z;
    float dy = b*currentPosition.y + currentPosition.x*currentPosition.z;
    float dz = c*currentPosition.z +(currentPosition.x*currentPosition.y)/3.0f;

    return Vec3(dx, dy, dz);
}

Vec3 Chenlee::getCameraPosition() const 
{
    return Vec3(75,75,75);
}

Vec3 Chenlee::getCameraTarget() const
{
return Vec3(0.0,0.0,0.0);
}

float Chenlee::getParticleSize() const
{
    return 0.15;
}