# strange-attractors
A C++ simulator for chaos attractors

## Description
strange-attractors is a `raylib` based simulator for modeling chaos attractors in 3D space. These attractors are governed by a set of differential equations that are deterministic. Despite this, it is impossible to predict the movements of particles under the influence of chaos attractors over the long term and thats what earns them their names. The simulator uses an object oriented design where each child attractor calculates its own derivative and passes those values to a parent class which holds a Fourth Order Runge-Kutta differential equation solver. The simulator current supports all of the following strange attractors:

### Attractors
1. The Lorenz Attractor
2. The Rössler Attractor
3. The Aizawa Attractor
4. The Halvorson Attractor
5. Thomas' Cyclically Cymmetric Attractor
6. The Chen-Lee Attractor
7. The Arneodo Attractor
8. The Sprott B Attractor
9. The Dadras Attractor
10. The Rabinovich-Fabrikant Attractor


## Usage
The only dependency for the simulator is `raylib` which can be installed using any package manager and then will be detected during the build process:
### Mac
`brew install raylib`
