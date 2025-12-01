//
// Created by Noah Graff on 11/30/25.
//

#ifndef SPH_FLUID_SIMULATION_VARIABLES_H
#define SPH_FLUID_SIMULATION_VARIABLES_H

inline int width = 1280;
inline int height = 720;

constexpr int numParticles = 500;
constexpr float particleSize = 1;

constexpr float smoothingRadius = 50.0f;
constexpr float targetDensity = 0.01f;
constexpr float pressureMultiplier = 100.0f;

constexpr float gravity = 0;
constexpr float mass = 1;

inline float densities[numParticles];

inline float deltaTime = 0;

#endif //SPH_FLUID_SIMULATION_VARIABLES_H