#include "attractor.hpp"

class Lorenz : Attractor
{

public:
    Lorenz(float &sigma, float &rho, float &beta);
    ~Lorenz();

    virtual Vec3 getNextStep(const Vec3 currentPosition, float dt) const override;

private:

    float sigma;
    float rho;
    float beta;

};


