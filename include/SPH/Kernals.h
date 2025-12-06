//
// Created by Noah Graff on 11/29/25.
//

#ifndef SPH_FLUID_SIMULATION_KERNALS_H
#define SPH_FLUID_SIMULATION_KERNALS_H
#include <__math/exponential_functions.h>
#include <cmath>

namespace Kernels {
    inline float spikyScalingFactor;
    inline float spikyDerivativeScalingFactor;

    inline float nearSpikyScalingFactor;
    inline float nearSpikyDerivativeScalingFactor;

    inline float viscosityScalingFactor;

    inline void calculateScalingFactors(const float radius) {
        spikyScalingFactor = static_cast<float>(6 / (M_PI * std::pow(radius, 4)));
        spikyDerivativeScalingFactor = static_cast<float>(12 / (M_PI * std::pow(radius, 4)));

        nearSpikyScalingFactor = static_cast<float>(10 / (M_PI * std::pow(radius, 5)));
        nearSpikyDerivativeScalingFactor = static_cast<float>(30 / (M_PI * std::pow(radius, 5)));

        viscosityScalingFactor = static_cast<float>(45 / (M_PI * std::pow(radius, 6)));
    }

    inline float Spiky(const float distance, const float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return v * v * spikyScalingFactor;
    }

    inline float NearSpiky(const float distance, const float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return v * v * v * nearSpikyScalingFactor;
    }

    inline float SpikyDerivative(const float distance, const float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return -v * spikyDerivativeScalingFactor;
    }

    inline float NearSpikyDerivative(const float distance, const float radius) {
        if (distance >= radius) return 0;

        const float v = radius - distance;
        return -v * v * nearSpikyDerivativeScalingFactor;
    }

    inline float ViscosityLaplacian(const float distance, const float radius) {
        if (distance >= radius) return 0;

        return (radius - distance) * viscosityScalingFactor;
    }
}

#endif //SPH_FLUID_SIMULATION_KERNALS_H