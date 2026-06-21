cmake_minimum_required(VERSION 3.16)
project(Projeto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Usar SFML incluida no projeto
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

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

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/source
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/SFML-2.6.2/bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets"
)
