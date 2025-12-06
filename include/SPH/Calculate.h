//
// Created by Noah Graff on 11/30/25.
//

#ifndef SPH_FLUID_SIMULATION_SIMULATOR_H
#define SPH_FLUID_SIMULATION_SIMULATOR_H
#include "Kernals.h"
#include "../Variables.h"

namespace Calculate {
    inline float Density(const int sampleIndex, Vector2 positionsToCheck[]) {
        float density = 0;

        const Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];
            const float distance = (samplePosition - particlePosition).magnitude();
            const float influence = Kernels::Spiky(distance, smoothingRadius);
            density += mass * influence;
        }

        return density;
    }

    inline float NearDensity(const int sampleIndex, Vector2 positionsToCheck[]) {
        float nearDensity = 0;

        const Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];
            const float distance = (samplePosition - particlePosition).magnitude();
            const float influence = Kernels::NearSpiky(distance, smoothingRadius);
            nearDensity += mass * influence;
        }

        return nearDensity;
    }

    inline float DensityToPressure(const float density) {
        const float densityError = density - targetDensity;
        return densityError * pressureMultiplier;
    }

    inline float SharedPressure(const float densityA, const float densityB) {
        const float pressureA = DensityToPressure(densityA);
        const float pressureB = DensityToPressure(densityB);
        return (pressureA + pressureB) / 2;
    }

    inline Vector2 PressureForce(const int sampleIndex, Vector2 positionsToCheck[]) {
        Vector2 pressureForce = Vector2::zero();

        Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];

            Vector2 offset = samplePosition - particlePosition;
            float distance = offset.magnitude();
            Vector2 direction = distance == 0 ? Vector2::randomDir() : offset / distance;

            float slope = Kernels::SpikyDerivative(distance, smoothingRadius);
            float density = densities[j][0];
            float sharedPressure = SharedPressure(density, densities[sampleIndex][0]);
            pressureForce -= direction * (sharedPressure * slope * mass) / density;
        }

        return pressureForce;
    }

    inline Vector2 NearPressureForce(const int sampleIndex, Vector2 positionsToCheck[]) {
        Vector2 nearPressureForce = Vector2::zero();

        Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];

            Vector2 offset = samplePosition - particlePosition;
            float distance = offset.magnitude();
            Vector2 direction = distance == 0 ? Vector2::randomDir() : offset / distance;

            float slope = Kernels::NearSpikyDerivative(distance, smoothingRadius);
            float density = densities[j][1];
            float sharedPressure = SharedPressure(density, densities[sampleIndex][1]);
            nearPressureForce -= direction * (sharedPressure * slope * mass) / density;
        }

        return nearPressureForce;
    }

    inline Vector2 ViscosityForce(const int sampleIndex, Vector2 positionsToCheck[]) {
        Vector2 viscosityForce;

        Vector2 samplePosition = positionsToCheck[sampleIndex];
        Vector2 sampleVelocity = velocities[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 velocityDifference = velocities[j] - sampleVelocity;

            Vector2 offset = samplePosition - positionsToCheck[j];
            float distance = offset.magnitude();
            float laplacian = Kernels::ViscosityLaplacian(distance, smoothingRadius);

            float density = densities[j][0];

            viscosityForce += velocityDifference * laplacian * mass / density;
        }

        return viscosityForce * viscosityMultiplier;
    }

    inline Vector2 ExternalForce(const int sampleIndex, Vector2 forcePosition) {
        const Vector2 offset = predictedPositions[sampleIndex] - forcePosition;
        const float distance = offset.magnitude();

        if (distance > mousePullRadius) return Vector2::zero();

        const Vector2 normal = offset.normalize();

        return normal * -mousePullMultiplier;
    }

    inline Color ColorFromVelocity(Vector2 velocity) {
        const float speed = velocity.magnitude();

        const float interpolation = std::min(speed / 5.0f, 1.0f);

        if (interpolation > 0.4) return Color::Lerp(midSpeedColor, fastColor, interpolation);

        return Color::Lerp(slowColor, midSpeedColor, interpolation);
    }
}

#endif //SPH_FLUID_SIMULATION_SIMULATOR_H