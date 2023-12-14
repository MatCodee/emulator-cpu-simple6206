# Configuración de archivos fuente en la carpeta src

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Agrega los archivos fuente al ejecutable principal
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} "../include/ExceptionHandler.h")