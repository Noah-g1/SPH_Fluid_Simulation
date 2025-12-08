//
// Created by Noah Graff on 12/6/25.
//

#ifndef SPH_FLUID_SIMULATION_ENTRY_H
#define SPH_FLUID_SIMULATION_ENTRY_H
#include <sys/types.h>

struct Entry {
    int particleIndex;
    uint cellKey;

    Entry() : particleIndex(0), cellKey(0) {}

    Entry(const int particleIndex, const uint cellKey) : particleIndex(particleIndex), cellKey(cellKey) {}

    void SetEntry(const int index, const uint key) {
        particleIndex = index;
        cellKey = key;
    }
};

#endif //SPH_FLUID_SIMULATION_ENTRY_H