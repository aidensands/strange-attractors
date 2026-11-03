#include "attractor.hpp"

class Lorenz : Attractor
{

public:
    Lorenz(float &sigma, float &rho, float &beta);
    ~Lorenz();

    virtual Update getNextStep() override;

private:

    float sigma;
    float rho;
    float beta;

};


