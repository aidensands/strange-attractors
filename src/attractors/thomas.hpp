#pragma once

#include "attractor.hpp"
#include "vec3.hpp"
#include <iostream>

using namespace std;


class Thomas : public Attractor {
    public:
        Thomas(){
            b = 0.208186f;
            cout << "Spawned Thomas Chaotic System!" << endl;
        }
        Vec3 initialState() const override;
        Vec3 derivative(const Vec3 &currentPosition) const override;
        Vec3 getCameraPosition() const override;
        Vec3 getCameraTarget() const override;
        float getParticleSize() const override;
    private:
        float b;
        string name = "Thomas";
};
