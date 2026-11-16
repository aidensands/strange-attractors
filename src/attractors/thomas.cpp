#include "vec3.hpp"
#include "thomas.hpp"
#include <cmath>



Vec3 Thomas::initialState() const
{
    return Vec3(1.1, 1.1, -0.01);
}

Vec3 Thomas::derivative(const Vec3 &currentPosition)const
{
    float dx = sinf(currentPosition.y) - b * currentPosition.x;
    float dy = sinf(currentPosition.z) - b * currentPosition.y;
    float dz = sinf(currentPosition.x) - b * currentPosition.z;
    return Vec3(dx, dy, dz);
}

Vec3 Thomas::getCameraPosition() const
{
     return Vec3(8.0,8.0,8.0);
}

Vec3 Thomas::getCameraTarget() const 
{
    return Vec3(0.0,0.0,0.0);
}

float Thomas::getParticleSize() const 
{
    return 0.04;
}