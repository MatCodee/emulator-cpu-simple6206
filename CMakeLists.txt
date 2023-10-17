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

#set(CMAKE_TOOLCHAIN_FILE "C:/Users/Matish/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


set(CMAKE_PREFIX_PATH "C:/Users/Matish/Documents/vcpkg/vcpkg/installed/x64-windows/share")
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)