#pragma once
#include "vec3.hpp"
#include <string>

using namespace std;

class Attractor
{

public:

    Attractor()
    {
        cameraPosition = Vec3(0.0, 0.0, 0.0);
        cameraTarget = Vec3(0.0, 0.0, 0.0);
    }

    virtual ~Attractor() = default;

    // Parent method for calculating the directional velocities of the particles
    // All children will override this with their own ODEs and those will be used in the parent getNextStep
    virtual Vec3 derivative(const Vec3 &currentPosition) const = 0;
    virtual Vec3 initialState() const = 0;
    virtual Vec3 getCameraPosition() const = 0;
    virtual Vec3 getCameraTarget() const = 0;
    virtual float getParticleSize() const = 0;
    // This is an override method, it will solve the given ODEs using the RK4 method
    Vec3 getNextStep(const Vec3 &currentPosition, float dt) const;

private:

    
    float particleSize;
    Vec3 cameraPosition;
    Vec3 cameraTarget;
    string name;
};


