#include "attractor.hpp"
#include <string>

Vec3 Attractor::getNextStep(const Vec3 &currentPosition, float dt) const
{
    // RK4 Estimation for solving the ODE
    Vec3 k1 = derivative(currentPosition);
    Vec3 k2 = derivative(currentPosition + k1 * (dt * 0.5f));
    Vec3 k3 = derivative(currentPosition + k2 * (dt * 0.5f));
    Vec3 k4 = derivative(currentPosition + k3 * dt);

    return currentPosition + (dt / 6.0f) * (k1 + k2 * 2.0f + k3 * 2.0f + k4);
}
