//
// Created by Noah Graff on 11/30/25.
//

#ifndef SPH_FLUID_SIMULATION_VARIABLES_H
#define SPH_FLUID_SIMULATION_VARIABLES_H

constexpr int numParticles = 100;
constexpr float particleSize = 10;

constexpr float smoothingRadius = 100.0f;
constexpr float targetDensity = 100.0f;
constexpr float pressureMultiplier = 500.0f;

constexpr float gravity = 0;
constexpr float mass = 1;

inline float densities[numParticles];

inline float deltaTime = 0;

#endif //SPH_FLUID_SIMULATION_VARIABLES_H