# strange-attractors
A C++ simulator for chaos attractors

## Description
strange-attractors is a `raylib` based simulator for modeling chaos attractors in 3D space. These attractors are governed by a set of orindary differential equations that are deterministic. Despite this, these attractors are highly sensitive to initial conditions which makes the long term prediction of their movements virtually impossible. The simulator uses an object oriented design where each child attractor calculates its own derivative and passes those values to a parent class which holds a Fourth Order Runge-Kutta differential equation estimator. Estimation allows us to compute particles position updates in linear time in terms of the number of particles. The simulator current supports all of the following strange attractors:

### Attractors
1. The Lorenz Attractor

$$\frac{dx}{dt}=\sigma(y-x)$$
$$\frac{dy}{dt}= x(\rho-z)-y$$
$$\frac{dz}{dt}=xy-\beta z$$

2. The Rössler Attractor

$$\frac{dx}{dt}=-y-z$$
$$\frac{dy}{dt}= x+ay$$
$$\frac{dz}{dt}=b+z(x-c)$$

3. The Aizawa Attractor

$$\frac{dx}{dt}=(z-b)x-dy$$
$$\frac{dy}{dt}=dx+(z-b)y$$
$$\frac{dz}{dt}=c+az-\frac{z^3}{3}-(x^2+y^2)(1+ez)+fzx^3$$

4. The Halvorson Attractor

$$\frac{dx}{dt}=-ax-4y-4z-y^2$$
$$\frac{dy}{dt}=-ay-4z-4x-z^2$$
$$\frac{dz}{dt}=-az-4x-4y-x^2$$

5. Thomas' Cyclically Symmetric Attractor

$$\frac{dx}{dt}=sin(y)-bx$$
$$\frac{dy}{dt}=sin(z)-by$$
$$\frac{dz}{dt}=sin(x)-bz$$

6. The Chen-Lee Attractor

$$\frac{dx}{dt}=ax-yz$$
$$\frac{dy}{dt}= by+xz$$
$$\frac{dz}{dt}=dz+\frac{xy}{3}$$

7. The Arneodo Attractor

$$\frac{dx}{dt}=y$$
$$\frac{dy}{dt}=z$$
$$\frac{dz}{dt}=-ax-by-z+cx^3$$

8. The Sprott B Attractor
9. The Dadras Attractor
10. The Rabinovich-Fabrikant Attractor
11. The Sprott-Linz F Attractor

$$\frac{dx}{dt}=y+z$$
$$\frac{dy}{dt}= -x+a*y$$
$$\frac{dz}{dt}=x^2-z$$

12. The Chua Circuit Attractor

$$\frac{dx}{dt}=\alpha(y-x-f(x))$$
$$\frac{dy}{dt}=x-y+z$$
$$\frac{dz}{dt}=z=-\beta y$$
$$f(x)=m_1x+\frac{1}{2}(m_0-m_1)(|x+1|-|x-1|)$$


## Usage
The only dependency for the simulator is `raylib` which can be installed using any package manager and then will be detected during the build process:
### Mac
**Install dependencies and Clone Repo**
```
brew install gcc cmake raylib
```
```
git clone https://github.com/aidensands/strange-attractors.git
```
**Build and Compile**
```
cmake -B build
```
```
cmake --build build --config Release
```
**Run the Executable**
```
./build/build/bin/strange-attractors
```