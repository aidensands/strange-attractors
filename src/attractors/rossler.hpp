#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class Rossler : public Attractor
{
    public:
        Rossler() : a(0.2f), b(0.2f), c(5.7f), name("Rossler")
        {
            cout << "Spawned a Rossler Attractor" << endl;
        }

        Vec3 derivative(const Vec3 &currentPosition) const override;
        Vec3 initialState() const override;
        Vec3 getCameraPosition() const override;
        Vec3 getCameraTarget() const override;
        float getParticleSize() const override;


    private:
        float a;
        float b;
        float c;
        string name;
};