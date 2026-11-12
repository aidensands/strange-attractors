#include "attractor.hpp"

class Lorenz : public Attractor
{

public:
    Lorenz(float sigma = 10.0f, float rho = 28.0f, float beta = 8.0f / 3.0f)
    : sigma(sigma), rho(rho), beta(beta) {}
    Lorenz(float &sigma, float &rho, float &beta);
    virtual Vec3 derivative(const Vec3 &currentPosition) const override;
    virtual Vec3 initialState() const override;


private:

    float sigma;
    float rho;
    float beta;

};


