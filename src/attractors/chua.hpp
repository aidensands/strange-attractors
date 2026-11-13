#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class Chua : public Attractor
{
    public:
        Chua() : alpha(15.6f), beta(28.0f)
        {
            cout << "Spawned a Chua Circuit Attractor" << endl;
        }
        Vec3 derivative(const Vec3 &currentPosition) const override;
        Vec3 initialState() const override;
        float getParticleSize() const override;
        Vec3 getCameraPosition() const override;
        Vec3 getCameraTarget() const override;
        
    private:
        float alpha;
        float beta;
};