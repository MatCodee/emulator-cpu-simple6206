cmake_minimum_required(VERSION 3.16)
project(Emulator6502 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Ejecutable principal con sus .cpp
file(GLOB SRC_FILES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(emulator ${SRC_FILES})

# 2) Carpeta de headers
target_include_directories(emulator
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include   # <memory.h>, <cpu.h>, <opcode.h>
)

# 3) (Opcional) tests
if (EXISTS "${PROJECT_SOURCE_DIR}/test")
    add_subdirectory(test)
endif()