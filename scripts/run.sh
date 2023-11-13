#!/bin/bash

cd ..
current_dir=$(pwd)

build_dir="$current_dir/build"

# Verificar si la carpeta build existe
if [ -d "$build_dir" ]; then
    # La carpeta build ya existe, entrar a ella
    cd "$build_dir/Debug"

    if [ -f Project.exe ]; then
        ./Project.exe  # Cambia esto a main.exe
    else
        echo "El archivo main.exe no se encontró."
    fi

    # Volver al directorio original
    cd "$current_dir"
fi

echo "Presiona Enter para continuar..."
read pausa