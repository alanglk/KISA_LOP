#!/bin/bash

# Directorios de entrada y salida
config_dir="./data/config"
output_dir="./data/output"

# Crear directorio de salida si no existe
mkdir -p "$output_dir"


run_script() {
    config_file="$1"
    base_name=$(basename "$config_file" .conf)
    output_file="$output_dir/$base_name.out"

    # Comprobar si el archivo de salida ya existe
    if [[ -f "$output_file" ]]; then
        echo "El archivo de salida '$output_file' ya existe. Saltando ejecución para '$config_file'."
    else
        ./build/main "$config_file" | tee "$output_file"
    fi
}

# Recorrer todos los archivos .conf en el directorio de configuración
for config_file in "$config_dir"/*.conf; do
    echo "Verificando archivo de configuración: $(basename "$config_file")"
    run_script "$config_file"
done

echo "Ejecutación completada :D !!!"
