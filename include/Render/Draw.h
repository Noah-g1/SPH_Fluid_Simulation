//
// Created by Noah Graff on 11/29/25.
//

#ifndef SPH_FLUID_SIMULATION_DRAW_H
#define SPH_FLUID_SIMULATION_DRAW_H
#include <SDL2/SDL_opengl.h>
#include "../Core/Vector2.h"
#include "../Core/Color.h"

namespace Draw {
    inline void triangle(const Vector2 vertex1,
                         const Vector2 vertex2,
                         const Vector2 vertex3,
                         const Color color) {

        bool nullPoint = vertex1 == NULL || vertex2 == NULL || vertex3 == NULL;
        if (nullPoint) {
            throw std::runtime_error("Warning: Invalid Position");
        }

        glBegin(GL_TRIANGLES);

        glColor3f(color.red, color.green, color.blue);
        glVertex2f(vertex1.x, vertex1.y);

        glVertex2f(vertex2.x, vertex2.y);

        glVertex2f(vertex3.x, vertex3.y);

        glEnd();
    }

    inline void circle(const Vector2 position, const float radius,
                       const Color color) {
        if (position == NULL) {
            throw std::runtime_error("Warning: Invalid Position");
        }

        const int numTriangles = radius < 50 ? 10 : static_cast<int>(radius / 3);

        for (int i = 0; i < numTriangles; i++) {
            const float angle1 = i * 2 * M_PI / numTriangles;
            const float angle2 = (i + 1) * 2 * M_PI / numTriangles;

            const float x1 = position.x + radius * cos(angle1);
            const float y1 = position.y + radius * sin(angle1);

            const float x2 = position.x + radius * cos(angle2);
            const float y2 = position.y + radius * sin(angle2);

            triangle(position, Vector2(x1, y1), Vector2(x2, y2), color);
        }
    }
}

#endif //SPH_FLUID_SIMULATION_DRAW_H