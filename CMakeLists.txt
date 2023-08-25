cmake_minimum_required(VERSION 3.12)
project(TuProyecto)

set(CMAKE_CXX_STANDARD 11)

# Agrega aquí todos los archivos fuente
set(SOURCES
    main.cpp
    memory.cpp
    cpu.cpp
)

# Agrega aquí todos los archivos de encabezado
set(HEADERS
    memory.h
    cpu.h
    opcode.h
)

add_executable(main ${SOURCES} ${HEADERS})