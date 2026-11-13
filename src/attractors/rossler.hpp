#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class Rossler : public Attractor
{
    public:
        Rossler() : a(0.2f), b(0.2f), c(5.7f)
        {
            cout << "Spawned a Rossler Attractor" << endl;
        }

        virtual Vec3 derivative(const Vec3 &currentPosition) const override;
        virtual Vec3 initialState() const override;
        virtual Vec3 getCameraPosition() const override;
        virtual Vec3 getCameraTarget() const override;
        virtual float getParticleSize() const override;


    private:
        float a;
        float b;
        float c;
        string name = "Rössler";
};