#pragma once

#include "attractor.hpp"
#include "vec3.hpp"
#include <iostream>

using namespace std;

class Chenlee : public Attractor
{
    public:
    Chenlee(){
        a = 5;
        b = -10;
        c = -3.8;
        cout << "Spawned Chenlee Chaotic System!" << endl;
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
    string name = "Chenlee";
};