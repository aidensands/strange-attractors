#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class Halvorson : public Attractor
{
    public:
        Halvorson() : a(1.4f)
        {
            cout << "Spawned a Halvorson Attractor";
        }

        virtual Vec3 derivative(const Vec3 &currentPosition) const override;
        virtual Vec3 initialState() const override;
        virtual Vec3 getCameraPosition() const override;
        virtual Vec3 getCameraTarget() const override;
        virtual float getParticleSize() const override;

    private:
        float a;
        string name = "Halvorson";
};