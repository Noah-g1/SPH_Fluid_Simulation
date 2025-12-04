//
// Created by Noah Graff on 11/29/25.
//

#ifndef SPH_FLUID_SIMULATION_KERNALS_H
#define SPH_FLUID_SIMULATION_KERNALS_H
#include <__math/exponential_functions.h>
#include <cmath>

namespace Kernals {
    inline float spikyScalingFactor;
    inline float spikyDerivativeScalingFactor;
    inline float viscosityScalingFactor;

    inline void calculateScalingFactors(float radius) {
        spikyScalingFactor = static_cast<float>(6 / (M_PI * std::pow(radius, 4)));
        spikyDerivativeScalingFactor = static_cast<float>(12 / (M_PI * std::pow(radius, 4)));

        viscosityScalingFactor = static_cast<float>(45 / (M_PI * std::pow(radius, 6)));
    }

    inline float Spiky(float distance, float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return v * v * spikyScalingFactor;
    }

    inline float SpikyDerivative(float distance, float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return -v * spikyDerivativeScalingFactor;
    }

    inline float ViscocityLaplacian(float distance, float radius) {
        if (distance >= radius) return 0;

        return (radius - distance) * viscosityScalingFactor;
    }
}

#endif //SPH_FLUID_SIMULATION_KERNALS_H