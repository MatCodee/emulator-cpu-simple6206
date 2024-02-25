#!/bin/bash

# Directorio actual

cd ..
current_dir=$(pwd)

# Ruta al directorio build
build_dir="$current_dir/build"

# Verificar si la carpeta build existe
if [ -d "$build_dir" ]; then
    # La carpeta build ya existe, entrar a ella
    cd "$build_dir"
else
    # La carpeta build no existe, crearla y luego entrar a ella
    mkdir -p "$build_dir"
    cd "$build_dir"
fi

# Ejecutar CMake
cmake ..

# Compilar el proyecto
cmake --build .

cd "$current_dir"


echo "Presiona Enter para continuar..."
read pausa