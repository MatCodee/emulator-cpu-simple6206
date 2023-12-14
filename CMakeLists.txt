
# cmake_minimum_required(VERSION 3.12)

# project(TuProyecto)

# set(CMAKE_CXX_STANDARD 11)



# # Agrega aquí todos los archivos fuente
# set(SOURCES
#     main.cpp
#     memory.cpp
#     cpu.cpp
# )

# # Agrega aquí todos los archivos de encabezado
# set(HEADERS
#     memory.h
#     cpu.h
#     opcode.h
# )

# #set(CMAKE_TOOLCHAIN_FILE "C:/Users/Matish/Documents/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


# add_executable(TestInstantiator TestInstantiator.cxx)
# target_link_libraries(TestInstantiator vtkCommon)
# add_test(NAME TestInstantiator COMMAND TestInstantiator)




# #set(CMAKE_PREFIX_PATH "C:/Users/Matish/Documents/vcpkg/vcpkg/installed/x64-windows/share")
# #find_package(fmt CONFIG REQUIRED)
# #target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)


cmake_minimum_required(VERSION 3.10)



project(Project)

set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)