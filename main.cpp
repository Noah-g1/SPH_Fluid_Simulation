#include "Vector2.h"
#include "Draw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

int width = 1280; int height = 720;

int numParticles = 100;

void start() {
    Vector2 positions[numParticles];
    Vector2 velocities[numParticles];
}

void update() {
    draw::circle(Vector2::zero(), 100);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_Window* window = SDL_CreateWindow(
        "Fluid Simulation",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!glContext) {
        std::cerr << "Window Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        std::cerr << "Warning: Unable to set VSync! " << SDL_GetError() << "\n";
    }

    SDL_GL_GetDrawableSize(window, &width, &height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-width, width,
        -height, height,
        -1.0, 1.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    bool running = true;
    SDL_Event event;

    start();
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update();

        SDL_GL_SwapWindow(window);
    }
;}