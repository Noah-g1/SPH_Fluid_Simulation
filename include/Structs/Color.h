//
// Created by Noah Graff on 12/4/25.
//

#ifndef SPH_FLUID_SIMULATION_COLOR_H
#define SPH_FLUID_SIMULATION_COLOR_H
#include <cmath>
#include <SDL2/SDL_opengl.h>

struct Color {
    GLfloat red;
    GLfloat green;
    GLfloat blue;

    constexpr Color(const GLfloat red, const GLfloat green, const GLfloat blue) : red(red), green(green), blue(blue) {}

    std::string toString() {
        return std::format("({}, {}, {})", red, blue, green);
    }

    static Color Lerp(const Color colorOne, const Color colorTwo, const float interpolation) {
        GLfloat red = std::lerp(colorOne.red, colorTwo.red, interpolation);
        GLfloat green = std::lerp(colorOne.green, colorTwo.green, interpolation);
        GLfloat blue = std::lerp(colorOne.blue, colorTwo.blue, interpolation);

        return {red, green, blue};
    }
};

#endif //SPH_FLUID_SIMULATION_COLOR_H