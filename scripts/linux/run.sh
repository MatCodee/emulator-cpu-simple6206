#!/bin/bash

cd ../../
current_dir=$(pwd)


build_dir="$current_dir/build"

# Verificar si la carpeta build existe
if [ -d "$build_dir" ]; then
    # La carpeta build ya existe, entrar a ella
    if [ -e Project ]; then
        echo $build_dir
        ./Project 
    else
        echo "El archivo ejecutable no se encontró."
    fi

    # Volver al directorio original
    cd "$current_dir"
fi

echo "Presiona Enter para continuar..."
read pausa
