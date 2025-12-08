cmake_minimum_required(VERSION 4.0)
project(SPH_Fluid_Simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (EXISTS "/opt/homebrew")
    set(HOMEBREW_PREFIX "/opt/homebrew")
elseif (EXISTS "/usr/local")
    set(HOMEBREW_PREFIX "/usr/local")
else()
    message(FATAL_ERROR "Homebrew not found!")
endif()

include_directories(${HOMEBREW_PREFIX}/include)
link_directories(${HOMEBREW_PREFIX}/lib)

find_library(SDL2_LIBRARY SDL2 PATHS ${HOMEBREW_PREFIX}/lib)

if (NOT SDL2_LIBRARY)
    message(FATAL_ERROR "SDL2 library not found in Homebrew directories!")
endif()

add_executable(SPH_Fluid_Simulation src/main.cpp
        include/Core/Vector2.h
        include/Render/Draw.h
        include/SPH/Kernals.h
        src/Simulation/Simulator.cpp
        include/SPH/Calculate.h
        include/Variables.h
        include/Core/Color.h
        include/SpacialHash/SpacialHash.h
        include/SpacialHash/Entry.h
)

target_link_libraries(SPH_Fluid_Simulation
        ${SDL2_LIBRARY}
        "-framework OpenGL"
)
