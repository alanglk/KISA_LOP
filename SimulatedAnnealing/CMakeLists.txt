cmake_minimum_required(VERSION 3.1)

project(SimulatedAnnealing
    VERSION 1.0
    DESCRIPTION "Implementation of Simulated Annealing Algoritm"
    LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Headers
include_directories(include)

# Agregar los archivos fuente comunes
set(SOURCES 
    src/LOP.cpp 
    src/Logger.cpp 
    src/SimulatedAnnealing.cpp
)
# Ejecutable principal
add_executable(main src/main.cpp ${SOURCES})

# Ejecutable de pruebas
add_executable(swap_testing src/swap_testing.cpp ${SOURCES})
