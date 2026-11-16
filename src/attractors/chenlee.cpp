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
    float dz = c*currentPosition.z +(currentPosition.x*currentPosition.y)/3;

    return Vec3(dx, dy, dz);
}

Vec3 Chenlee::getCameraPosition() const 
{

}

Vec3 Chenlee::getCameraTarget() const
{

}

float Chenlee::getParticleSize() const
{

}