#include "../include/Render/Draw.h"
#include "Simulation/Simulator.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

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

    glOrtho(-width * windowScaling, width * windowScaling,
        -height * windowScaling, height * windowScaling,
        -1.0, 1.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Uint32 nowTickTime = SDL_GetPerformanceCounter();
    Uint32 lastTickTime = 0;

    SDL_KeyCode key_code;

    SDL_Event event;
    bool running = true;

    Simulator::Start();
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == 13) {
                        simulationStarted = !simulationStarted;
                    }

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseDown = false;
                    break;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        lastTickTime = nowTickTime;
        nowTickTime = SDL_GetPerformanceCounter();

        deltaTime = static_cast<float>(nowTickTime - lastTickTime) * (10 / static_cast<float>(SDL_GetPerformanceFrequency()));

        if (mouseDown) {
            Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
            //SDL_GetWindowPosition(window, &windowX, &windowY);

            mouseX -= width / 2;
            mouseX *= windowScaling * 2;
            mouseY -= height / 2;
            mouseY *= -windowScaling * 2;
        }

        Simulator::Update();

        SDL_GL_SwapWindow(window);
    }
;}