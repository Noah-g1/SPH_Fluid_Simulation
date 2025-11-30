//
// Created by Noah Graff on 11/30/25.
//

#ifndef SPH_FLUID_SIMULATION_SIMULATOR_H
#define SPH_FLUID_SIMULATION_SIMULATOR_H
#include "Vector2.h"
#include "Kernals.h"
#include "../Variables.h"

namespace Calculate {
    inline float Density(int sampleIndex, Vector2 positionsToCheck[]) {
        float density = 0;

        Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];
            const float distance = (samplePosition - particlePosition).magnitude();
            const float influence = Kernals::Spiky(distance, smoothingRadius);
            density += mass * influence;

            std::cout << influence << std::endl;
        }

        return density;
    }

    inline float DensityToPressure(float density) {
        const float densityError = density - targetDensity;
        return densityError * pressureMultiplier;
    }

    inline float SharedPressure(float densityA, float densityB) {
        const float pressureA = DensityToPressure(densityA);
        const float pressureB = DensityToPressure(densityB);
        return (pressureA + pressureB) / 2;
    }

    inline Vector2 PressureForce(int sampleIndex, Vector2 positionsToCheck[]) {
        Vector2 pressureForce = Vector2::zero();

        Vector2 samplePosition = positionsToCheck[sampleIndex];

        for (int j = 0; j < numParticles; j++) {
            if (sampleIndex == j) continue;

            Vector2 particlePosition = positionsToCheck[j];

            Vector2 offset = samplePosition - particlePosition;
            float distance = offset.magnitude();
            Vector2 direction = distance == 0 ? Vector2::randomDir() : offset / distance;

            float slope = Kernals::SpikyDerivative(distance, smoothingRadius);
            float density = densities[j];
            float sharedPressure = SharedPressure(density, densities[sampleIndex]);
            pressureForce -= direction * (sharedPressure * slope * mass) / density;
        }

        return pressureForce;
    }
}

#endif //SPH_FLUID_SIMULATION_SIMULATOR_H