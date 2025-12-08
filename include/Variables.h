//
// Created by Noah Graff on 11/30/25.
//

#ifndef SPH_FLUID_SIMULATION_VARIABLES_H
#define SPH_FLUID_SIMULATION_VARIABLES_H
#include "Core/Color.h"
#include "Core/Vector2.h"

inline int width = 1280;
inline int height = 720;
inline float windowScaling = (1.0 / 10);

inline int mouseX, mouseY;
inline int windowX, windowY;

inline bool simulationStarted = false;
inline bool mouseDown = false;

inline Color fastColor = Color(1.0, 0.25, 0);
inline Color midSpeedColor = Color(0, 1, 0.5);
inline Color slowColor = Color(0, 0.25, 1.0);

constexpr int numParticles = 500;
constexpr float particleSize = 1.5;

constexpr float smoothingRadius = 20;
constexpr float targetDensity = 0.035;
constexpr float pressureMultiplier = 200;
constexpr float viscosityMultiplier = 2;

constexpr float mousePullRadius = 100;
constexpr float mousePullMultiplier = 0.06;

constexpr float gravity = 0.9;
constexpr float mass = 1;

inline float deltaTime = 0;

inline Vector2 positions[numParticles];
inline Vector2 predictedPositions[numParticles];

inline Vector2 velocities[numParticles];

inline float densities[numParticles][2];

#endif //SPH_FLUID_SIMULATION_VARIABLES_H