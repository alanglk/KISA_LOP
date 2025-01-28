# Mínimo requerido
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(KISA_LOP)

# Carpeta con headers
include_directories(include)

# Archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Crear ejecutable
add_executable(programa ${SOURCES})