//
// Created by Noah Graff on 11/30/25.
//

#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include "../../include/Math/Vector2.h"
#include "../../include/Math/Kernals.h"
#include "../../include/Math/Calculate.h"
#include "../../include/Render/Draw.h"
#include "../../include/Variables.h"

namespace Simulator {
    inline Vector2 positions[numParticles];
    inline Vector2 predictedPositions[numParticles];

    inline Vector2 velocities[numParticles];

    inline void SpawnParticles() {
        int particlesPerRow = static_cast<int>(sqrt(numParticles));
        int particlesPerCol = (numParticles - 1) / particlesPerRow + 1;
        float spacing = particleSize * 2 + 5;

        for (int i = 0; i < numParticles; i++) {
            float x = (i % particlesPerRow - particlesPerRow / 2 + 0.5f) * spacing;
            float y = (i / particlesPerRow - particlesPerCol / 2 + 0.5f) * spacing;

            positions[i].x = x;
            positions[i].y = y;
        }
    }

    inline void DrawParticles() {
        for (int i = 0; i < numParticles; i++) {
            Draw::circle(positions[i], particleSize);
        }
    }

    inline void HandleBorderCollisions(int index) {
        Vector2 &position = positions[index];
        Vector2 &velocity = velocities[index];

        Vector2 halfSize = Vector2(width, height) / 4;
        Vector2 boxCenter = Vector2::zero();

        Vector2 max = boxCenter + halfSize;

        Vector2 positionSign = position.sign();

        if (abs(position.x - boxCenter.x) > max.x) {
            position.x = max.x * positionSign.x;
            velocity.x *= -0.01f;
        }

        if (abs(position.y - boxCenter.y) > max.y) {
            position.y = max.y * positionSign.y;
            velocity.y *= -0.01f;
        }
    }

    inline void SimulationStep() {
        for (int i = 0; i < numParticles; i++) {
            velocities[i] += Vector2::down() * (gravity * deltaTime);
            predictedPositions[i] = positions[i] + velocities[i] * deltaTime;
        }

        for (int i = 0; i < numParticles; i++) {
            densities[i] = Calculate::Density(i, predictedPositions);
        }

        for (int i = 0; i < numParticles; i++) {
            Vector2 pressureForce = Calculate::PressureForce(i, predictedPositions);
            Vector2 pressureAcceleration = pressureForce / densities[i];
            velocities[i] += (pressureAcceleration) * deltaTime;
        }

        for (int i = 0; i < numParticles; i++) {
            positions[i] += velocities[i] * deltaTime;
            HandleBorderCollisions(i);
        }
    }

    inline void Start() {
        Kernals::calculateScalingFactors(smoothingRadius);

        SpawnParticles();
    }

    inline void Update() {
        DrawParticles();

        try {
            SimulationStep();
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}