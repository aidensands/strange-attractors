#pragma once

#include "attractor.hpp"
#include "vec3.hpp"
#include <iostream>

using namespace std;

class Aizawa : public Attractor
{

public:

    Aizawa()
    {
        a = 0.95;
        b = 0.7;
        c = 0.6;
        d = 3.5;
        e = 0.25;
        f = 0.1;

        cout << "Spawned Aizawa Chaotic System!" << endl;

    }

    Vec3 initialState() const override;
    Vec3 derivative(const Vec3 &currentPosition) const override;
    Vec3 getCameraPosition() const override;
    Vec3 getCameraTarget() const override;
    float getParticleSize() const override;

private:
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
};