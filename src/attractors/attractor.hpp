#pragma once
#include "vec3.hpp"


class Attractor
{

public:
    virtual ~Attractor() = default;

    // Parent method for calculating the directional velocities of the particles
    // All children will override this with their own ODEs and those will be used in the parent getNextStep
    virtual Vec3 derivative(const Vec3 &currentPosition) const = 0;
    virtual Vec3 initialState() const = 0;
    // This is an override method, it will solve the given ODEs using the RK4 method
    Vec3 getNextStep(const Vec3 &currentPosition, float dt) const;

private:


};


