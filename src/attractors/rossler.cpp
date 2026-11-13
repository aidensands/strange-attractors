#include "rossler.hpp"


Vec3 Rossler::derivative(const Vec3 &currentPosition) const 
{
   float dx = -currentPosition.y - currentPosition.z;
   float dy = currentPosition.x + a * currentPosition.y;
   float dz = b + currentPosition.z * (currentPosition.x - c);

   return Vec3(dx, dy, dz);
}

Vec3 Rossler::initialState() const 
{
    return Vec3(0.0, 0.0, 0.0);
}

Vec3 Rossler::getCameraPosition() const
{
    return Vec3(5.0, 5.0, 5.0);
}

Vec3 Rossler::getCameraTarget() const
{
    return Vec3(0.0, 0.0, 0.0);
}

float Rossler::getParticleSize() const
{
    return 0.05;
}