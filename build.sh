#!/bin/bash
# g++ -fdiagnostics-color=always -I "./data" -g "./src/main.cpp" -o "./build/main.out"

BUILD_DIR="./build"
SRC_FILE="./src/main.cpp"
OUTPUT_FILE="$BUILD_DIR/main.out"
INCLUDE_DIR="."

# Crear carpeta build si no existe
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creando el directorio $BUILD_DIR..."
    mkdir -p "$BUILD_DIR"
else
    echo "Limpiando el directorio $BUILD_DIR..."
    rm -rf "$BUILD_DIR"/*
fi

g++ -fdiagnostics-color=always -I "$INCLUDE_DIR" -g "$SRC_FILE" -o "$OUTPUT_FILE" -fopenmp

