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

    inline void calculateScalingFactors(float radius) {
        spikyScalingFactor = static_cast<float>(15 / M_PI * std::pow(radius, 6));
        spikyDerivativeScalingFactor = static_cast<float>(-10 / (M_PI * std::pow(radius, 6)));
    }

    inline float Spiky(float distance, float radius) {
        if (distance >= radius) return 0;

        return static_cast<float>(std::__math::pow(radius - distance, 3) * spikyScalingFactor);
    }

    inline float SpikyDerivative(float distance, float radius) {
        if (distance >= radius) return 0;

        return (radius - distance) * (radius - distance) * spikyDerivativeScalingFactor;
    }
}

#endif //SPH_FLUID_SIMULATION_KERNALS_H