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

    // This function is for the specific attractor's dx, dy, dz which is returned in a Vec3
    virtual Vec3 derivative(const Vec3 &currentPosition) const = 0;
    
    // This is a single Vec3 containing the origin coordinates for all particles
    // Some systems recommend specific starting conditions
    virtual Vec3 initialState() const = 0;
    
    // This is where the camera will be positioned in space
    virtual Vec3 getCameraPosition() const = 0;
    
    // This is where the camera will be facing in space
    virtual Vec3 getCameraTarget() const = 0;
    
    // This is the particle size control, some systems look better with smaller or larger particles
    virtual float getParticleSize() const = 0;
    
    // This is a RK4 ODE solver for just the parent class, no child class should touch this
    Vec3 getNextStep(const Vec3 &currentPosition, float dt) const;

private:

    float particleSize;
    Vec3 cameraPosition;
    Vec3 cameraTarget;
    string name;
};


