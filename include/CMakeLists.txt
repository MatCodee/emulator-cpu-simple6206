# Configuración de archivos de encabezado en la carpeta include

file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Agrega los archivos de encabezado como directorios de inclusión
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})