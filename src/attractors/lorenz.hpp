#pragma once

#include "attractor.hpp"
#include <iostream>

using namespace std;

class Lorenz : public Attractor
{

public:
    Lorenz(float sigma = 10.0f, float rho = 28.0f, float beta = 8.0f / 3.0f)
    : sigma(sigma), rho(rho), beta(beta), name("Lorenz")
    {
        cout << "Spawned Lorenz Chaotic System!" << endl;
    }
    Lorenz(float &sigma, float &rho, float &beta);
    Vec3 derivative(const Vec3 &currentPosition) const override;
    Vec3 initialState() const override;
    Vec3 getCameraPosition() const override;
    Vec3 getCameraTarget() const override;
    float getParticleSize() const override;

private:

    float sigma;
    float rho;
    float beta;
    string name;
};


