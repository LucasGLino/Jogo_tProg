cmake_minimum_required(VERSION 3.16)
project(Projeto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Usar SFML do MSYS2 MINGW64
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 2.6 REQUIRED COMPONENTS Graphics Window System)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/Include/*.hpp"
    "${CMAKE_SOURCE_DIR}/Include/*.h"
)

foreach(file ${SRC_FILES})
    if(${file} MATCHES ".*/CMakeFiles/.*" OR ${file} MATCHES ".*/build/.*")
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
endforeach()

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/source
)