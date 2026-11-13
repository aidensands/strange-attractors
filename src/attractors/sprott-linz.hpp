#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class SprottLinz : public Attractor
{
    public:
        SprottLinz() : a(0.5)
        {
            cout << "Spawned a Sprott-Linz Attractor" << endl;
        }
        Vec3 derivative(const Vec3 &currentPosition) const override;
        Vec3 initialState() const override;
        float getParticleSize() const override;
        Vec3 getCameraPosition() const override;
        Vec3 getCameraTarget() const override;
        
    private:
        float a;
};