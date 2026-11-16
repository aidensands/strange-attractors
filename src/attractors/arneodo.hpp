#pragma once

#include "attractor.hpp"
#include "vec3.hpp"
#include <iostream>

using namespace std;

class Arneodo : public Attractor
{
    public:
    
    Arneodo(){
        a = -5.5;
        b = 3.5;
        c = 1;
        cout << "Spawned Arneodo Chaotic System!" << endl;
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
    string name = "Arneodo";

};