cmake_minimum_required(VERSION 3.10)

project(Project)

set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)