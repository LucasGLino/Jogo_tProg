cmake_minimum_required(VERSION 3.16)
project(Projeto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Caminho para a SFML 2.6.2
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

# 🔍 Busca recursivamente todos os arquivos .cpp e .hpp/.h
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.hpp"
    "${CMAKE_SOURCE_DIR}/*.h"
)

# 🧹 Remove arquivos do CMake e da pasta de build
foreach(file ${SRC_FILES})
    if(${file} MATCHES ".*/CMakeFiles/.*" OR ${file} MATCHES ".*/build/.*")
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
endforeach()

# Cria o executável com todos os arquivos encontrados
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Vincula as bibliotecas SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Opcional: inclui automaticamente todos os diretórios para #include
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)