#include "vec3.hpp"


class Attractor
{

public:
    Attractor() = default;
    ~Attractor() = default;

    // Parent method for calculating the directional velocities of the particles
    // All children will override this with their own ODEs and those will be used in the parent getNextStep
    virtual Vec3 derivative(const Vec3 currentPosition) = 0;
    virtual Vec3 initialState() = 0;
    // This is an override method, it will solve the given ODEs using the RK4 method
    virtual Vec3 getNextStep(const Vec3 currentPosition, float dt) const;

private:


};


