//
// Created by Noah Graff on 12/6/25.
//

#ifndef SPH_FLUID_SIMULATION_SPACIALHASH_H
#define SPH_FLUID_SIMULATION_SPACIALHASH_H
#include <climits>
#include "Entry.h"
#include "../Core/Vector2.h"

class SpacialHash {
    const int hashK1 = 15823;
    const int hashK2 = 9737333;

    Entry* spacialLookup;
    int* startIndices;
    Vector2* points;
    float radius;
    int numPoints;

    SpacialHash(Vector2* points, const int numPoints, const float radius) : radius(radius) {
        spacialLookup = new Entry[numPoints];
        startIndices = new int[numPoints];
        this->points = points;

        this->radius = radius;
        this->numPoints = numPoints;
    }

    ~SpacialHash() {
        delete[] points;
        delete[] spacialLookup;
        delete[] startIndices;
    }

    void UpdateSpacialLookup(Vector2 updatedPoints[]) {
        points = updatedPoints;

        for (int i = 0; i < numPoints; i++) {
            auto [cellX, cellY] = PositionToCellCoord(updatedPoints[i]);
            const uint cellKey = GetKeyFromHash(HashCell(cellX, cellY));
            spacialLookup[i].SetEntry(i, cellKey);
            startIndices[i] = INT_MAX;
        }

        SortSpacialLookup();

        for (int i = 0; i < numPoints; i++) {
            const uint key = spacialLookup[i].cellKey;
            const uint keyPrev = i == 0 ? UINT32_MAX : spacialLookup[i - 1].cellKey;

            if (key != keyPrev) {
                startIndices[key] = i;
            }
        }
    }

    [[nodiscard]]
    std::pair<int, int> PositionToCellCoord(Vector2 position) const {
        const int x = static_cast<int>(position.x / radius);
        const int y = static_cast<int>(position.y / radius);

        return {x, y};
    }

    [[nodiscard]]
    uint HashCell(const int x, const int y) const {
        const uint a = static_cast<uint>(x * hashK1);
        const uint b = static_cast<uint>(y * hashK2);

        return a + b;
    }

    [[nodiscard]]
    uint GetKeyFromHash(const uint hash) const {
        return hash % numPoints;
    }

private:
    void SortSpacialLookup() {
        Entry* temp = new Entry[numPoints];
        MergeSort(spacialLookup, temp, 0, numPoints - 1);
    }

    static void MergeSort(Entry* &toSort, Entry* &temp, const int low, const int high) {
        if (low == high) return;

        const int mid = (low + high) / 2;
        MergeSort(toSort, temp, 0, mid);
        MergeSort(toSort, temp, mid + 1, high);
        Merge(toSort, temp, low, high);
    }

    static void Merge(Entry* &toSort, Entry* &temp, const int low, const int high) {
        const int mid = (low + high) / 2;

        int i = low;
        int j = mid + 1;
        int k = low;

        while (i <= mid && j <= high) {
            if (toSort[i].cellKey <= toSort[j].cellKey) {
                temp[k++] = toSort[i++];
            } else {
                temp[k++] = toSort[j++];
            }
        }

        while (i <= mid) temp[k++] = toSort[i++];
        while (j <= high) temp[k++] = toSort[j++];

        for (int index = low; index <= high; index++) {
            toSort[index] = temp[index];
        }
    }
};

#endif //SPH_FLUID_SIMULATION_SPACIALHASH_H