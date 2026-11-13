#include "chua.hpp"

static float f(float x)
{
    // Nonlinear function for diode modeling, required for chuas ODE

    float m0 = static_cast<float>(-8/7);   
    float m1 = static_cast<float>(-5/7);

    return m1 * x  + 0.5f * (m0 - m1) * (abs(x + 1.0f) - abs(x - 1.0f));
}

Vec3 Chua::derivative(const Vec3 &currentPosition) const
{
    float dx = alpha * (currentPosition.y - currentPosition.x - f(currentPosition.x));
    float dy = currentPosition.x - currentPosition.y + currentPosition.z;
    float dz = -beta * currentPosition.y;

    return Vec3(dx, dy, dz);
}


Vec3 Chua::initialState() const
{
    return Vec3(0.1, 0.1, 0.1);
}

Vec3 Chua::getCameraPosition() const
{
    return Vec3(0.0, 0.0, 0.0);
}

Vec3 Chua::getCameraTarget() const
{
    return Vec3(0.1, 0.1, 0.1);
}

float Chua::getParticleSize() const
{
    return 0.05;
}