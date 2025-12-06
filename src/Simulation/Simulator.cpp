//
// Created by Noah Graff on 11/30/25.
//

#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <SDL2/SDL_events.h>

#include "../../include/SPH/Kernals.h"
#include "../../include/SPH/Calculate.h"
#include "../../include/Variables.h"
#include "../../include/Render/Draw.h"

namespace Simulator {
    inline void SpawnParticles() {
        int particlesPerRow = static_cast<int>(sqrt(numParticles));
        int particlesPerCol = (numParticles - 1) / particlesPerRow + 1;
        float spacing = particleSize * 2 + 2;

        for (int i = 0; i < numParticles; i++) {
            float x = (i % particlesPerRow - particlesPerRow / 2 + 0.5f) * spacing;
            float y = (i / particlesPerRow - particlesPerCol / 2 + 0.5f) * spacing;

            positions[i].x = x;
            positions[i].y = y;
        }
    }

    inline void DrawParticles() {
        for (int i = 0; i < numParticles; i++) {
            Color particleColor = Calculate::ColorFromVelocity(velocities[i]);

            Draw::circle(positions[i], particleSize, particleColor);
        }
    }

    inline void HandleBorderCollisions(int index) {
        Vector2 &position = positions[index];
        Vector2 &velocity = velocities[index];

        Vector2 halfSize = Vector2(width / 4, height / 4) / 4;
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
        const Vector2 gravityVector = Vector2::down() * (gravity * deltaTime);

        for (int i = 0; i < numParticles; i++) {
            velocities[i] += gravityVector;
            predictedPositions[i] = positions[i] + velocities[i] * deltaTime;
        }

        for (int i = 0; i < numParticles; i++) {
            densities[i][0] = Calculate::Density(i, predictedPositions);
            densities[i][1] = Calculate::NearDensity(i, predictedPositions);
        }

        for (int i = 0; i < numParticles; i++) {
            Vector2 pressureForce = Calculate::PressureForce(i, predictedPositions);
            Vector2 viscosityForce = Calculate::ViscosityForce(i, predictedPositions);
            Vector2 mouseForce;

            if (mouseDown) {
                mouseForce = Calculate::ExternalForce(i, Vector2(mouseX, mouseY));
            }

            velocities[i] += (pressureForce + viscosityForce + mouseForce) * deltaTime / densities[i][0];

            Vector2 nearPressure = Calculate::NearPressureForce(i, predictedPositions);
            Vector2 nearPressureAcceleration = nearPressure * deltaTime / densities[i][1];

            velocities[i] += nearPressureAcceleration;
        }

        for (int i = 0; i < numParticles; i++) {
            positions[i] += velocities[i] * deltaTime;
            HandleBorderCollisions(i);
        }
    }

    inline void Start() {
        Kernels::calculateScalingFactors(smoothingRadius);

        SpawnParticles();
    }

    inline void Update() {
        DrawParticles();

        if (!simulationStarted) return;

        try {
            SimulationStep();
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}